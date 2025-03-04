/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_memory_collector.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:29 by szhong            #+#    #+#             */
/*   Updated: 2025/02/17 16:03:31 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_collector.h"

static t_list **get_expansion_mem_list(void)
{
	static t_list *expansion_mem_list = NULL;
	return (&expansion_mem_list);
}

char *track_expanded_str(char *str)
{
	t_list **expansion_mem_list;
	t_list *current;

	if (!str)
		return (NULL);
	expansion_mem_list = get_expansion_mem_list();
	current = *expansion_mem_list;
	while (current)
	{
		if (current->content == str)
			return (str);
		current = current->next;
	}
	ft_lstadd_back(expansion_mem_list, ft_lstnew(str));
	return (str);
}

void cleanup_expanded_strings(void)
{
	t_list **expansion_mem_list;
	t_list *current;
	t_list *next;

	expansion_mem_list = get_expansion_mem_list();
	current = *expansion_mem_list;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*expansion_mem_list = NULL;
} 