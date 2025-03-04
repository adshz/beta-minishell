/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor_external_cmd.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:56:06 by szhong            #+#    #+#             */
/*   Updated: 2025/02/21 15:56:23 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "utils/utils.h"

static void	extern_cleanup_resources(char *cmd_path, char **env_array)
{
	if (cmd_path)
		free(cmd_path);
	if (env_array)
		ft_free_array(env_array);
}

static int	prepare_command(t_shell *shell, t_ast_node *node,
						char **cmd_path, char ***env_array)
{
	if (!node || !node->args || !node->args[0])
		return (1);
	*cmd_path = get_command_path(shell, node->args[0], shell->env);
	if (!*cmd_path)
	{
		ft_putstr_fd("ERROR: Command path not found\n", 2);
		return (127);
	}
	*env_array = create_env_array(shell->env);
	if (!*env_array)
	{
		free(*cmd_path);
		perror("minishell: get_env_array");
		return (1);
	}
	return (0);
}

static void	cleanup_and_exit_external(t_shell *shell, int status)
{
	cleanup_shell(shell);
	ft_heredoc_memory_collector(NULL, true);
	ft_hash_memory_collector(NULL, true);
	exit(status);
}

static int	extern_handle_child_process(t_shell *shell, t_ast_node *node,
							char *cmd_path, char **env_array)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ret = command_executor_execute_child_process(shell, node, \
											cmd_path, env_array);
	extern_cleanup_resources(cmd_path, env_array);
	cleanup_current_command(shell);
	cleanup_env_cache(shell);
	cleanup_and_exit_external(shell, ret);
	return (ret);
}

static int	extern_handle_fork_error(char *cmd_path, char **env_array)
{
	extern_cleanup_resources(cmd_path, env_array);
	return (1);
}

int	execute_external_command(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
	char	*cmd_path;
	char	**env_array;
	int		ret;

	ret = prepare_command(shell, node, &cmd_path, &env_array);
	if (ret != 0)
		return (ret);
	pid = fork();
	if (pid == -1)
		return (extern_handle_fork_error(cmd_path, env_array));
	if (pid == 0)
		return (extern_handle_child_process(shell, node, cmd_path, env_array));
	extern_cleanup_resources(cmd_path, env_array);
	return (handle_external_parent_process(pid));
}
