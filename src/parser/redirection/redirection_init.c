/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:39:44 by szhong            #+#    #+#             */
/*   Updated: 2025/01/28 13:39:49 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

/**
 * @brief Creates appropriate redirection node based on token type
 * @param type Token type
 * @param file_value File token value
 * @return Redirection node or NULL on failure
 */
static t_ast_node	*init_heredoc_data(t_ast_node *redir_node, \
									const char *file_value)
{
	char	*delimiter;

	redir_node->data.content_fd = -1;
	redir_node->data.content_path = NULL;
	delimiter = ft_strdup(file_value);
	if (!delimiter)
	{
		free(redir_node);
		return (NULL);
	}
	delimiter = ft_heredoc_memory_collector(delimiter, false);
	redir_node->data.delimiter = delimiter;
	redir_node = ft_heredoc_memory_collector(redir_node, false);
	return (redir_node);
}

static t_ast_node	*init_redirection_by_type(t_token_type type, \
										const char *file_value)
{
	t_ast_node	*redir_node;

	redir_node = NULL;
	if (type == TOKEN_REDIRECT_OUT)
		redir_node = create_ast_node(AST_REDIR_OUT, NULL);
	else if (type == TOKEN_REDIRECT_IN)
		redir_node = create_ast_node(AST_REDIR_IN, NULL);
	else if (type == TOKEN_APPEND)
		redir_node = create_ast_node(AST_REDIR_APPEND, NULL);
	else if (type == TOKEN_HEREDOC)
	{
		redir_node = create_ast_node(AST_HEREDOC, NULL);
		if (redir_node)
			return (init_heredoc_data(redir_node, file_value));
	}
	return (redir_node);
}

t_ast_node	*create_redirection_node(t_token_type type, const char *filename)
{
	t_ast_node	*node;
	t_ast_node	*file_node;

	node = init_redirection_by_type(type, filename);
	if (!node)
		return (NULL);
	node = track_ast_node(node);
	file_node = create_redir_file_node(filename, node);
	if (!file_node)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
