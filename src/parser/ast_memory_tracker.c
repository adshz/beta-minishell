/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_memory_tracker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:16:31 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:16:40 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

t_list	**get_ast_mem_list(void)
{
	static t_list	*ast_mem_list;

	ast_mem_list = NULL;
	return (&ast_mem_list);
}

t_ast_node	*track_ast_node(t_ast_node *node)
{
	t_list	**ast_mem_list;
	t_list	*current;

	if (!node)
		return (NULL);
	ast_mem_list = get_ast_mem_list();
	current = *ast_mem_list;
	while (current)
	{
		if (current->content == node)
			return (node);
		current = current->next;
	}
	ft_lstadd_back(ast_mem_list, ft_lstnew(node));
	return (node);
}

void	cleanup_ast_nodes(void)
{
	t_list	**ast_mem_list;
	t_list	*current;
	t_list	*next;

	ast_mem_list = get_ast_mem_list();
	current = *ast_mem_list;
	while (current)
	{
		next = current->next;
		if (current->content)
			free_ast(current->content);
		free(current);
		current = next;
	}
	*ast_mem_list = NULL;
}
