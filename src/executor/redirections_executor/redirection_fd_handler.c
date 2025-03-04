/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_fd_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:46:41 by szhong            #+#    #+#             */
/*   Updated: 2025/02/18 00:47:00 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../executor.h"
#include "core/core.h"

void	cleanup_saved_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		close(saved_stdin);
		if (getpid() == getppid())
			track_fd(STDIN_FILENO);
	}
	if (saved_stdout != -1)
	{
		close(saved_stdout);
		if (getpid() == getppid())
			track_fd(STDOUT_FILENO);
	}
}

void	cleanup_and_exit(int saved_stdin, int saved_stdout, int status)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	exit(status);
}

int	setup_saved_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		print_error("dup", "Failed to save stdin", 1);
		return (1);
	}
	if (track_fd(*saved_stdin) == -1)
	{
		close(*saved_stdin);
		print_error("track_fd", "Failed to track saved stdin", 1);
		return (1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		print_error("dup", "Failed to save stdout", 1);
		return (1);
	}
	if (track_fd(*saved_stdout) == -1)
	{
		close(*saved_stdin);
		close(*saved_stdout);
		print_error("track_fd", "Failed to track saved stdout", 1);
		return (1);
	}
	return (0);
}
