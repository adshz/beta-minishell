/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:47:52 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:55:44 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
#include "lexer/lexer.h"

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node	*ast;
	t_token		*current;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected toke '|'", \
				STDERR_FILENO);
		return (NULL);
	}
	current = tokens;
	ast = parse_expression(&current);
	if (!ast)
		return (NULL);
	if (current != NULL)
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
