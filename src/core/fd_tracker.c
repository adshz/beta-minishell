/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tracker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:29 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:26:10 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "utils/utils.h"
#include "memory_collector/memory_collector.h"

static t_list	**get_fd_list(void)
{
	static t_list	*fd_list;

	fd_list = NULL;
	return (&fd_list);
}

int	track_fd(int fd)
{
	t_list	**fd_list;
	t_list	*current;
	int		*fd_ptr;

	if (fd < 0)
		return (-1);
	fd_list = get_fd_list();
	current = *fd_list;
	while (current)
	{
		fd_ptr = current->content;
		if (fd_ptr && *fd_ptr == fd)
			return (fd);
		current = current->next;
	}
	fd_ptr = malloc(sizeof(int));
	if (!fd_ptr)
		return (-1);
	*fd_ptr = fd;
	fd_ptr = ft_hash_memory_collector(fd_ptr, false);
	ft_lstadd_back(fd_list, tracked_lstnew(fd_ptr));
	return (fd);
}

void	cleanup_fds(void)
{
	t_list	**fd_list;
	t_list	*current;
	int		*fd_ptr;

	fd_list = get_fd_list();
	if (!fd_list || !*fd_list)
		return ;
	current = *fd_list;
	while (current)
	{
		fd_ptr = current->content;
		if (fd_ptr && *fd_ptr > STDERR_FILENO)
			close(*fd_ptr);
		current = current->next;
	}
	*fd_list = NULL;
}
