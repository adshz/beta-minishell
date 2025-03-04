/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tracker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:29 by szhong            #+#    #+#             */
/*   Updated: 2025/02/17 16:03:31 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static t_list **get_fd_list(void)
{
	static t_list *fd_list = NULL;
	return (&fd_list);
}

int	track_fd(int fd)
{
	t_list **fd_list;
	t_list *current;
	int *fd_ptr;

	if (fd < 0)
		return (-1);
	ft_printf("PID %d: Attempting to track FD: %d\n", getpid(), fd);  // Debug
	fd_list = get_fd_list();
	current = *fd_list;
	while (current)
	{
		fd_ptr = current->content;
		if (fd_ptr && *fd_ptr == fd)
		{
			ft_printf("PID %d: FD %d already tracked\n", getpid(), fd);  // Debug
			return (fd);
		}
		current = current->next;
	}
	fd_ptr = malloc(sizeof(int));
	if (!fd_ptr)
		return (-1);
	*fd_ptr = fd;
	ft_lstadd_back(fd_list, ft_lstnew(fd_ptr));
	ft_printf("PID %d: Successfully tracked FD: %d\n", getpid(), fd);  // Debug
	return (fd);
}

void cleanup_fds(void)
{
	t_list **fd_list;
	t_list *current;
	t_list *next;
	int *fd_ptr;

	ft_printf("PID %d: Starting FD cleanup...\n", getpid());  // Debug
	fd_list = get_fd_list();
	if (!fd_list || !*fd_list)
	{
		ft_printf("PID %d: No FDs to clean\n", getpid());  // Debug
		return;
	}
	current = *fd_list;
	while (current)
	{
		next = current->next;
		fd_ptr = current->content;
		if (fd_ptr)
		{
			ft_printf("PID %d: Found FD: %d\n", getpid(), *fd_ptr);  // Debug
			if (*fd_ptr > STDERR_FILENO)
			{
				ft_printf("PID %d: Closing FD: %d\n", getpid(), *fd_ptr);  // Debug
				close(*fd_ptr);
			}
			free(fd_ptr);
		}
		free(current);
		current = next;
	}
	*fd_list = NULL;
	ft_printf("PID %d: FD cleanup complete\n", getpid());  // Debug
} 