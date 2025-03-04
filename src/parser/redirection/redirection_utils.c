/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:40:07 by szhong            #+#    #+#             */
/*   Updated: 2025/01/28 13:40:12 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

static t_ast_node	*setup_redirection_nodes(t_token *current,
										t_token *file_token,
										t_ast_node *result)
{
	t_ast_node	*redir_node;
	t_ast_node	*file_node;

	redir_node = create_redirection_node(current->type, file_token->value);
	if (!redir_node)
		return (NULL);
	redir_node = track_ast_node(redir_node);
	if (current->type != TOKEN_HEREDOC)
	{
		file_node = create_file_node(file_token, redir_node);
		if (!file_node)
			return (NULL);
		redir_node->right = file_node;
	}
	if (!result)
	{
		redir_node->left = NULL;
		return (redir_node);
	}
	if (is_redirection_type(result->type))
	{
		redir_node->left = result;
		return (redir_node);
	}
	redir_node->left = result;
	return (redir_node);
}

/**
 * @brief Processes redirection token and creates nodes
 * @param current Current token
 * @param result Current result tree
 * @return Updated result tree or NULL on failure
 */
t_ast_node	*process_redirection(t_token *current, t_ast_node *result)
{
	t_token		*file_token;

	file_token = current->next;
	if (!validate_file_token(file_token))
		return (NULL);
	if (current->type == TOKEN_REDIRECT_IN)
		check_input_file(file_token->value);
	return (setup_redirection_nodes(current, file_token, result));
}
