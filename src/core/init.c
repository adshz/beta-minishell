/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:43:27 by szhong            #+#    #+#             */
/*   Updated: 2025/01/20 17:08:16 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "core.h"
#include "shell.h"
#include "types.h"


static void	init_pwd(t_shell *shell)
{
	char	*tmp;

	if (!hashmap_search(shell->env, "PWD"))
	{
		tmp = getcwd(NULL, 0)
		if (!tmp)
			return ;
		hashmap_insert(shell->env, "PWD", tmp, 0);
		free(tmp);
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
	init_pwd(shell);
	init_shlvl(shell);
	if (!hashmap_search(shell->env, "PATH"))
		hashmap_insert(shell->env, "PATH", \
				 "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0)
	if (!hashmap_search(shell->env, "_"))
		hashmap_insert(shell->env, "_", argv[0], 0)
	hashmap_remove(shell->env, "OLDPWD");
}

/**
 * @brief Initialises the shell structure and its environement
 *
 * This function performs the complete initialisation of the shell structure:
 *  - Initialise all members of t_shell with zeros
 *  - Sets up environement variables using hash table data structure
 *  - Creates file descriptor backups for I/O restoration
 *  - Confgures terminal settings
 *  - Initialises core environement variables such as PWD, SHIVL, PATH
 *  - Sets up shell process ID
 *
 * The function is called at the beginning of shell (see/main.c)
 *
 * @param shell  Pointer of t_shell type to the shell structure to initailise
 * @param argv   Array of command line arguments
 * @param envp   Array of environment variables (can be NULL)
 * 
 *
 * @note If environment initialisation fails, the function exits with ERROR
 * status
 * @note File descriptors are backed up for handling pipes and redirections
 * @note Terminal settings are saved for proper signal handling
 *
 * @see cleanup_shell() for corresponding cleanup
 * @see init_env_vars() for environment variable initialisation
 * @see get_shell_pid() for getting shell process ID
 * 
 */
void	init_shell(t_shell *shell, char *argv[], char *envp[])
{
	ft_memset(shell, 0, sizeof(t_shell));
	if (!envp)
		shell->env = hashmap_create();
	else
		shell->env = env_to_hash(envp);
	if (!shell->env)
	{
		handle_error(shell, ERR_ENV, \
			   "Environment variable initialisation failed");
		exit(EXIT_ERROR);
	}
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &shell->term_settings);
	init_env_vars(shell, argv);
	get_shell_pid(shell);
}
