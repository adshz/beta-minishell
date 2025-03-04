/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_experssion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:57:14 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:57:25 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

static t_ast_node	*handle_initial_redirections(t_token **tokens,
		t_shell *shell)
{
	t_ast_node	*node;

	node = NULL;
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		node = parse_redirection_construct(node, tokens, shell);
		if (!node)
			return (NULL);
	}
	return (node);
}

static t_ast_node	*handle_pipeline_node(t_token **tokens,
		t_ast_node *node, t_shell *shell)
{
	t_ast_node	*cmd;

	if (!*tokens || is_redirection_token((*tokens)->type))
		return (node);
	if (node)
	{
		cmd = parse_pipeline(tokens, shell);
		if (!cmd)
			return (NULL);
		node->left = cmd;
		return (node);
	}
	return (parse_pipeline(tokens, shell));
}

static t_ast_node	*handle_final_redirections(t_token **tokens,
		t_ast_node *node, t_shell *shell)
{
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		node = parse_redirection_construct(node, tokens, shell);
		if (!node)
			return (NULL);
	}
	return (node);
}

t_ast_node	*build_expression_tree(t_token **tokens, t_shell *shell)
{
	t_ast_node	*node;

	node = handle_initial_redirections(tokens, shell);
	if (!*tokens && !node)
		return (NULL);
	node = handle_pipeline_node(tokens, node, shell);
	if (!node)
		return (NULL);
	return (handle_final_redirections(tokens, node, shell));
}
