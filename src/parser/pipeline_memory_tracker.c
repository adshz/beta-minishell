/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_memory_tracker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:59:40 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:00:50 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"
#include "utils/utils.h"

static t_list	**get_pipeline_mem_list(void)
{
	static t_list	*pipeline_mem_list;

	pipeline_mem_list = NULL;
	return (&pipeline_mem_list);
}

t_ast_node	*track_pipeline_node(t_ast_node *node)
{
	t_list	**pipeline_mem_list;
	t_list	*current;

	if (!node)
		return (NULL);
	pipeline_mem_list = get_pipeline_mem_list();
	current = *pipeline_mem_list;
	while (current)
	{
		if (current->content == node)
			return (node);
		current = current->next;
	}
	ft_lstadd_back(pipeline_mem_list, tracked_lstnew(node));
	return (node);
}

void	cleanup_pipeline_nodes(void)
{
	t_list	**pipeline_mem_list;
	t_list	*current;
	t_list	*next;

	pipeline_mem_list = get_pipeline_mem_list();
	if (!pipeline_mem_list || !*pipeline_mem_list)
		return ;
	current = *pipeline_mem_list;
	while (current)
	{
		next = current->next;
		if (current->content && !((t_ast_node *)current->content)->is_freed)
		{
			free_ast(current->content);
		}
		current = next;
	}
	*pipeline_mem_list = NULL;
}
