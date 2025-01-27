/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:43:27 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 14:52:29 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "core.h"
#include "shell.h"
#include "errors.h"
#include "hashtable/hashtable.h"

static void	cleanup_intialisation(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->stdin_backup >= 0)
		close(shell->stdin_backup);
	if (shell->stdout_backup >= 0)
		close(shell->stdout_backup);
	if (shell->env)
	{
		hashmap_destory(shell->env);
		shell->env = NULL;
	}
	ft_memset(shell, 0, sizeof(t_shell));
}

static int	init_io(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
	{
		ft_putendl_fd("Failed to backup file descriptors", STDERR_FILENO);
		return (ERROR);
	}
	if (tcgetattr(STDIN_FILENO, &shell->term_settings) == -1)
	{
		ft_putendl_fd("Failed to get terminal attributes", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

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
	if (!shell)
		return (ERROR);
	ft_memset(shell, 0, sizeof(t_shell));
	if (init_env(shell, envp) == SUCCESS && init_io(shell) == SUCCESS && \
	get_shell_pid == SUCCESS)
	{
		init_env_vars(shell, argv);
		return (SUCCESS);
	}
	cleanup_initialisation(shell);
	return (ERROR);
}
