/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:38:10 by szhong            #+#    #+#             */
/*   Updated: 2025/01/28 13:38:24 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"
#include "memory_collector/memory_collector.h"

static void	init_node_data(t_ast_node *node, t_ast_type type)
{
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->value = NULL;
	node->is_expanded = 0;
	node->original = NULL;
	node->data.content_path = NULL;
	node->data.content_fd = -1;
	node->data.delimiter = NULL;
	node->is_freed = false;
}

static t_ast_node	*parser_handle_heredoc(t_ast_node *node, char *value)
{
	node->value = value;
	return (node);
}

static t_ast_node	*parser_handle_node_value(t_ast_node *node, t_ast_type type,
									char *tracked_value)
{
	if (type == AST_HEREDOC)
	{
		node = parser_handle_heredoc(node, tracked_value);
		if (!node)
			return (NULL);
	}
	else
		node->value = tracked_value;
	return (node);
}

static t_ast_node	*parser_handle_no_value(t_ast_node *node, t_ast_type type)
{
	if (type == AST_HEREDOC)
		node = ft_heredoc_memory_collector(node, false);
	return (node);
}

t_ast_node	*create_ast_node(t_ast_type type, char *value)
{
	t_ast_node	*node;
	char		*new_value;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	init_node_data(node, type);
	node = track_ast_node(node);
	if (!value)
		return (parser_handle_no_value(node, type));
	new_value = ft_strdup(value);
	if (!new_value)
		return (NULL);
	node = parser_handle_node_value(node, type, new_value);
	if (!node || !node->value)
		return (NULL);
	return (node);
}
