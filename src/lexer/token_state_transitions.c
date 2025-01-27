/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state_transitions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:35:07 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:44:35 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

/**
 * @brief Handles transitions from normal state
 *
 * @param c Current character
 * @return Next state based on character
 */
static t_tokeniser_state	handle_normal_state(char c)
{
	if (c == '\\')
		return (STATE_IN_BACKSLASH);
	if (c == '\'')
		return (STATE_IN_SINGLE_QUOTE);
	if (c == '\"')
		return (STATE_IN_DOUBLE_QUOTE);
	return (STATE_NORMAL);
}

/**
 * @brief Handles transitions from double quote state
 *
 * @param c Current character
 * @param was_backslash Pointer to backslash state
 * @return Next state based on character and backslash state
 */
static t_tokeniser_state	handle_double_quote_state(char c, \
												int *was_backslash)
{
	if (c == '\\' && !(*was_backslash))
	{
		*was_backslash = 1;
		return (STATE_IN_BACKSLASH);
	}
	if (c == '\"' && !(*was_backslash))
		return (STATE_NORMAL);
	*was_backslash = 0;
	return (STATE_IN_DOUBLE_QUOTE);
}
