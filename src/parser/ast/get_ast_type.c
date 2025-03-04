/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ast_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:04:56 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 00:04:59 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

t_ast_type	get_ast_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (AST_PIPE);
	if (type == TOKEN_REDIRECT_IN)
		return (AST_REDIR_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (AST_REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (AST_REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (AST_HEREDOC);
	if (type == TOKEN_AND)
		return (AST_AND);
	if (type == TOKEN_OR)
		return (AST_OR);
	return (AST_COMMAND);
}
