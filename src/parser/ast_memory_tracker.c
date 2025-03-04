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

t_ast_node *track_ast_node(t_ast_node *node, bool clean_flag)
{
    t_list **ast_mem_list;

    ast_mem_list = get_ast_mem_list();
    if (clean_flag)
    {
        ft_lstclear(ast_mem_list, (void (*)(void *))free_ast);
        *ast_mem_list = NULL;
        return (NULL);
    }
    else if (node)
    {
        ft_lstadd_back(ast_mem_list, ft_lstnew(node));
        return (node);
    }
    return (NULL);
}

void cleanup_ast_nodes(void)
{
    track_ast_node(NULL, true);
} 