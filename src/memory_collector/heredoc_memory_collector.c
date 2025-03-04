/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_memory_collector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:32:32 by szhong            #+#    #+#             */
/*   Updated: 2025/02/26 18:33:09 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "memory_collector.h"

static t_list	**get_heredoc_mem_list(void)
{
	static t_list	*heredoc_mem_list = NULL;

	return (&heredoc_mem_list);
}

void	*ft_heredoc_memory_delone(void *ptr)
{
	t_list	**current;
	t_list	*tmp;
	t_list	**heredoc_mem_list;

	if (!ptr)
		return (NULL);
	heredoc_mem_list = get_heredoc_mem_list();
	if (!*heredoc_mem_list)
		return (NULL);
	current = heredoc_mem_list;
	while (*current)
	{
		if ((*current)->content == ptr)
		{
			tmp = *current;
			*current = (*current)->next;
			ft_lstdelone(tmp, ft_delete_mem);
			return (NULL);
		}
		current = &(*current)->next;
	}
	return (NULL);
}

void	*ft_heredoc_memory_collector(void *ptr, bool clean_flag)
{
	t_list	**heredoc_mem_list;

	heredoc_mem_list = get_heredoc_mem_list();
	if (clean_flag)
	{
		ft_lstclear(heredoc_mem_list, ft_delete_mem);
		*heredoc_mem_list = NULL;
		return (NULL);
	}
	else
	{
		ft_lstadd_back(heredoc_mem_list, ft_lstnew(ptr));
		return (ptr);
	}
}
