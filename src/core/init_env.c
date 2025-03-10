/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:44:27 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 14:59:30 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "core.h"
#include "errors.h"
#include "hashtable/hashtable.h"
#include "types.h"

/**
 * @brief Initialises or increments the SHLVL (Shell Level) enviornment variable
 *
 * This static function manages the shell level counter, which tracks how many
 * nested shell deep we are. It either initialises SHLVL to 1 or increments to
 * the existing value
 *
 * @param shell Pointer to the shell structure containing environement variable
 *
 * @note SHLVL defaults to 1 if not present or invalid
 * @note Reports envorinment variable errors via handle_error
 * 
 * @see hashmap_search() for environement variable lookup
 * @see ft_itoa() for integer to string conversion
 * @see handle_error() for error reporting
 */
static void	init_shlvl(t_shell *shell)
{
	char	*key;
	char	*value;

	key = tracked_strdup("SHLVL");
	value = tracked_strdup("1");
	if (!key || !value)
	{
		handle_error(shell, ERROR_ENV, "Environment variable SHLVL failure");
		return ;
	}
	hashmap_insert(shell->env, key, value, 0);
	mark_env_modified(shell);
}

/**
 * @brief Initialises the PWD (Present working directory) environement variable
 *
 * This static function checks if PWD exists in the environment variable,
 * if not, the function sets the current present working directory to PWD.
 * getcwd() dynamically allocates memory 
 *
 * @param shell Pointer to the shell structure containing environment hashmap
 * 
 * @note Only sets PWD if it doesn't already exist in environment
 * @note Uses getcwd(NULL, 0) for dynamic buffer allocation
 * @note Handles memory cleanup after hashmap insertion
 * @note Report errors through handle_error if getcwd() fails
 *
 * @see hashmap_search() for environment variable lookup
 * @see hashmap_insert() for environment variable setting
 * @see getcwd() for current working directory retrieval
 * @see handle_error() for error reporting 
 */
static void	init_pwd(t_shell *shell)
{
	char	*tmp;
	char	*key;

	key = tracked_strdup("PWD");
	if (!key)
		return ;
	if (!hashmap_search(shell->env, key))
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
		{
			handle_error(shell, ERROR_PWD_ACCESS, \
				"Cannot determine current working directory");
			return ;
		}
		tmp = ft_hash_memory_collector(tmp, false);
		hashmap_insert(shell->env, key, tmp, 0);
		mark_env_modified(shell);
	}
}

/**
 * @brief Initialises the shell's environment variables
 *
 * This function sets up the environment hashtable with size of 1024 \
 * for the shell:\n
 *   - Creates an empty hashtable if envp is NULL
 *   - Converts the environment array to a hashtable if envp exits
 *
 * @param shell Pointer to the shell structure
 * @param envp Array of environment variable in "key=value" format (can be NULL)
 * @return SUCCESS if initialisation succeeds, ERROR otherwise
 *
 * @note if envp is NULL, an empty hashtable is created
 * @note Environment variables are stored in a hashtable for O(1) lookup time
 *
 * @see 
 * - hashmap_create() for empty envp hashtable creation
 * - env_to_hashtable() for environment array conversion.
 */
int	init_env(t_shell *shell, char *envp[])
{
	if (!envp)
		shell->env = hashmap_create();
	else
		shell->env = env_to_hashtable(envp);
	if (shell->env)
		return (SHELL_SUCCESS);
	ft_putendl_fd("Environment variable initialisation failure", STDERR_FILENO);
	return (SHELL_ERROR);
}

static void	setup_default_path(t_shell *shell)
{
	char	*path;
	char	*path_key;

	path = tracked_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	path_key = tracked_strdup("PATH");
	if (path && path_key)
	{
		hashmap_insert(shell->env, path_key, path, 0);
		mark_env_modified(shell);
	}
}

/**
 * @brief Initialises essential environement variables for the shell
 *
 * This function sets up the core environement variables required for shell
 * operation
 *   - PWD: Current working directory (via init_pwd())
 *   - SHLVL: Shell level counter (via init_shlvl())
 *   - PATH: System path for executable lookup (if not already set)
 *   - _ : Name of the shell executable
 *
 * The function also removes OLDPWD to ensue clean directory tracking
 *
 * @param shell Pointer to the shell structure containing environment hashmap
 * @param agrv Array of command line arguments (argv[0] is ./minishell)
 *
 * @note PATH is only set if not already present in environement
 * @note Default PATH includes standard system directories
 * @note OLDPWD is explicitly removed to ensure clean PWD tracking
 *
 * @see init_pwd() for PWD initialisation
 * @see init_shlvl() for shell level handling
 * @see hashmap_search() for environement variable lookup
 * @see hashmap_insert() for environment variable setting
 *
 * Example:
 * @code
 * t_shell shell;
 * char *argv[] = {"./minishell", NULL};
 * init_env_var(&shell, argv);
 * @endcode
 */
void	init_env_vars(t_shell *shell, char *argv[])
{
	char	*arg0;
	char	*underscore_key;
	char	*oldpwd_key;

	init_pwd(shell);
	init_shlvl(shell);
	if (!hashmap_search(shell->env, "PATH"))
		setup_default_path(shell);
	if (!hashmap_search(shell->env, "_"))
	{
		arg0 = tracked_strdup(argv[0]);
		underscore_key = tracked_strdup("_");
		if (arg0 && underscore_key)
		{
			hashmap_insert(shell->env, underscore_key, arg0, 0);
			mark_env_modified(shell);
		}
	}
	oldpwd_key = tracked_strdup("OLDPWD");
	if (oldpwd_key)
	{
		hashmap_remove(shell->env, oldpwd_key);
		mark_env_modified(shell);
	}
}
