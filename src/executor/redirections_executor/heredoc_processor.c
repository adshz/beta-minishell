/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:25:06 by szhong            #+#    #+#             */
/*   Updated: 2025/02/18 00:25:35 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../executor.h"
#include "utils/utils.h"

static void	cleanup_heredoc(int pipe_fds[2], int saved_stdin,
						int saved_stdout, t_shell *shell)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cleanup_saved_fds(saved_stdin, saved_stdout);
	shell->in_heredoc = 0;
	g_signal_status = SIG_NONE;
	ft_heredoc_memory_collector(NULL, true);
}

static int	process_heredoc_loop(t_ast_node *node, int pipe_fds[2],
							t_shell *shell, int saved_fds[2])
{
	char	*line;
	int		ret;

	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		ret = handle_heredoc_line(line, pipe_fds, node, shell);
		if (ret != 0)
		{
			cleanup_heredoc(pipe_fds, saved_fds[0], saved_fds[1], shell);
			return (ret);
		}
		if (write_heredoc_line(line, pipe_fds, node))
			break ;
	}
	return (0);
}

int	collect_heredoc_content(t_ast_node *node, t_shell *shell)
{
	int		pipe_fds[2];
	int		saved_fds[2];
	int		ret;

	ret = setup_heredoc(node, pipe_fds, shell);
	if (ret != 0)
		return (ret);
	if (setup_saved_fds(&saved_fds[0], &saved_fds[1]) != 0)
		return (1);
	ret = process_heredoc_loop(node, pipe_fds, shell, saved_fds);
	if (ret != 0)
		return (ret);
	node->data.content_fd = pipe_fds[0];
	close(pipe_fds[1]);
	cleanup_saved_fds(saved_fds[0], saved_fds[1]);
	shell->in_heredoc = 0;
	g_signal_status = SIG_NONE;
	return (0);
}

int	setup_heredoc_pipe(t_ast_node *node)
{
	int	old_fd;

	if (!node || node->data.content_fd < 0)
	{
		ft_heredoc_memory_collector(NULL, true);
		return (print_error("heredoc", "invalid file descriptor", 1));
	}
	old_fd = node->data.content_fd;
	if (dup2(old_fd, STDIN_FILENO) == -1)
	{
		close(old_fd);
		ft_heredoc_memory_collector(NULL, true);
		return (print_error("heredoc", "dup2 failed", 1));
	}
	close(old_fd);
	node->data.content_fd = -1;
	return (0);
}

int	handle_heredoc(t_ast_node *node, t_shell *shell)
{
	int	ret;

	ret = collect_heredoc_content(node, shell);
	return (ret);
}
