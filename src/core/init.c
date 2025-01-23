/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:43:27 by szhong            #+#    #+#             */
/*   Updated: 2025/01/23 16:55:10 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "core.h"
#include "shell.h"
#include "errors.h"
#include "hashtable/hashtable.h"

/**
 * @brief Gets the shell's process ID using fork technique
 *
 * This function determines the shell's PID by using a fork() trick;
 * 1. Creates a child process using fork()
 * 2. Child process exits immediately
 * 3. Parent process waits for child to exit
 * 4. Parent process calculates its PID using child's PID
 *
 * The calculation works because
 *  - fork() returns child's PID to parent
 *  - Child PIDs are typically parent's PID + 1
 *  - Therefore parent's PID = child's PID -1
 *
 * @param shell Pointer to the shell structure to store PID
 *
 * @note Exits program if fork fails;
 */
static int	get_shell_pid(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("Child Process Fork Failure & Failed to get shell PID", \
				STDERR_FILENO);
		return (ERROR);
	}
	if (pid == 0)
		exit(SUCCESS);
	waitpid(pid, NULL, 0);
	shell->pid = pid - 1;
	return (SUCCESS);
}

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
	char	*tmp;
	int		shlvl;

	shlvl = 1;
	tmp = hashmap_search(shell->env, "SHLVL");
	if (tmp && ft_atoi(tmp) > 0)
		shlvl = ft_atoi(tmp) + 1;
	tmp = ft_itoa(shlvl);
	if (!tmp)
	{
		handle_error(shell, ERR_ENV, "Environment variable SHLVL failure");
		return ;
	}
	hashmap_insert(shell->env, "SHLVL", tmp, 0);
	free(tmp);
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

	if (!hashmap_search(shell->env, "PWD"))
	{
		tmp = getcwd(NULL, 0)
		if (!tmp)
		{
			handle_error(shell, ERR_NOT_FOUND, "Current Directory Not Found");
			return ;
		}
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
	{
		hashmap_insert(shell->env, "PATH", \
				 "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", 0);
		return ;
	}
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
 * @return SUCCESS OR ERROR
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
int	init_shell(t_shell *shell, char *argv[], char *envp[])
{
	ft_memset(shell, 0, sizeof(t_shell));
	if (!envp)
		shell->env = hashmap_create();
	else
		shell->env = env_to_hashtable(envp);
	if (!shell->env)
	{
		ft_putendl_fd("Environment variable initialisation failed", \
				STDERR_FILENO);
		cleanup_shell(shell);
		return (ERROR);
	}
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &shell->term_settings);
	init_env_vars(shell, argv);
	if (get_shell_pid(shell) != SUCCESS)
	{
		cleanup_shell(shell);
		return (ERROR);
	}
	return (SUCCESS);
}
