/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:20 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:07:17 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&')
}

static int	is_operator(const char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strcmp(str, "||", 2) == 0)
		return (1);
	if (ft_strcmp(str, "&&", 2) == 0)
		return (1);
	if (ft_strcmp(str, "<<", 2) == 0)
		return (1);
	if (ft_strcmp(str, ">>", 2) == 0)
		return (1);
	return (0);
}

t_token_type	get_token_type(const char *value)
{
	if (!value || !*value)
		return (TOKEN_EOF);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(value, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(value, "||") == 0)
		return (TOKEN_OR);
	return (TOKEN_WORD);
}
