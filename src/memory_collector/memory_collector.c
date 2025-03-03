/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_collector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:32:32 by szhong            #+#    #+#             */
/*   Updated: 2025/02/26 18:33:09 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "memory_collector.h"

static t_list	**get_hash_mem_list(void)
{
	static t_list	*hash_mem_list = NULL;

	return (&hash_mem_list);
}

void	*ft_hash_memory_collector(void *ptr, bool clean_flag)
{
	t_list	**hash_mem_list;

	hash_mem_list = get_hash_mem_list();
	if (clean_flag)
	{
		ft_lstclear(hash_mem_list, ft_delete_mem);
		*hash_mem_list = NULL;
		return (NULL);
	}
	else
	{
		ft_lstadd_back(hash_mem_list, ft_lstnew(ptr));
		return (ptr);
	}
}

void	*ft_memory_collector(t_shell *shell, void *ptr, bool clean_flag)
{
	if (clean_flag)
	{
		ft_lstclear(&shell->mem_list, ft_delete_mem);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&shell->mem_list, ft_lstnew(ptr));
		return (ptr);
	}
}
