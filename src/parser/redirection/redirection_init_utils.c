/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_init_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:59:10 by szhong            #+#    #+#             */
/*   Updated: 2025/02/21 10:01:14 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static t_ast_node	*create_heredoc_file_node(t_ast_node *redir_node)
{
	t_ast_node	*file_node;
	char		*value;

	file_node = NULL;
	value = ft_strdup(redir_node->data.delimiter);
	if (!value)
	{
		free_ast(redir_node);
		return (NULL);
	}
	value = ft_heredoc_memory_collector(value, false);
	file_node = create_ast_node(AST_COMMAND, value);
	if (!file_node)
	{
		free_ast(redir_node);
		return (NULL);
	}
	file_node = ft_heredoc_memory_collector(file_node, false);
	return (file_node);
}

static t_ast_node	*create_regular_file_node(t_ast_node *redir_node, \
										const char *file_value)
{
	t_ast_node	*file_node;

	file_node = NULL;
	file_node = create_ast_node(AST_COMMAND, (char *)file_value);
	if (!file_node)
	{
		free_ast(redir_node);
		return (NULL);
	}
	return (file_node);
}

t_ast_node	*create_redir_file_node(const char *file_value, \
								t_ast_node *redir_node)
{
	t_ast_node	*file_node;

	file_node = NULL;
	if (redir_node->type == AST_HEREDOC)
		file_node = create_heredoc_file_node(redir_node);
	else
		file_node = create_regular_file_node(redir_node, file_value);
	if (!file_node)
		return (NULL);
	redir_node->right = file_node;
	return (redir_node);
}
