/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_memory_tracker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:00 by your_username     #+#    #+#             */
/*   Updated: 2024/03/19 10:00:00 by your_username    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list **get_ast_mem_list(void)
{
    static t_list *ast_mem_list = NULL;
    return (&ast_mem_list);
}

t_ast_node *track_ast_node(t_ast_node *node)
{
    t_list **ast_mem_list;

    if (!node)
        return (NULL);
    ast_mem_list = get_ast_mem_list();
    ft_lstadd_back(ast_mem_list, ft_lstnew(node));
    return (node);
}

void cleanup_ast_nodes(void)
{
    t_list **ast_mem_list;
    t_list *current;
    t_list *next;

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