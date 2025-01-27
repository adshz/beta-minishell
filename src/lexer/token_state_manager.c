/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:28 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 17:59:30 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

/**
 * @brief Determines next tokenizer state based on current state and character
 *
 * Handles state transitions for:
 * - Backslash escaping
 * - Single quotes
 * - Double quotes
 * - Normal state
 *
 * State machine logic:
 * - Backslash -> Normal (after processing escaped char)
 * - Normal -> Backslash/Single/Double quote states
 * - Quote states -> Normal (when matching quote found)
 *
 * @param current_state Current tokenizer state
 * @param c            Current character being processed
 * @return Next state for tokenizer
 *
 * @note Maintains backslash state between calls
 * @see t_tokenizer_state for possible states
 */
t_tokeniser_state	get_next_state(t_tokeniser_state current_state, char c)
{
	static int	was_backslash;

	if (current_state == STATE_IN_BACKSLASH)
	{
		was_backslash = 0;
		return (STATE_NORMAL);
	}
	if (current_state == STATE_NORMAL)
	{
		if (c == '\\')
			return (STATE_IN_BACKSLASH);
		if (c == '\'')
			return (STATE_IN_SINGLE_QUOTE);
		if (c == '\"')
			return (STATE_IN_DOUBLE_QUOTE);
	}
	else if (current_state == STATE_IN_DOUBLE_QUOTE)
	{
		if (c == '\\' && !was_backslash)
		{
			was_backslash = 1;
			return (STATE_IN_BACKSLASH);
		}
		if (c == '\"' && !was_backslash)
			return (STATE_NORMAL);
		was_backslash = 0;
	}
	else if (current_state == STATE_IN_SINGLE_QUOTE \
		&& c == '\'')
		return (STATE_NORMAL);
	return (current_state);
}

/**
 * @brief Calculates length of next token considering quoting and escaping
 *
 * Token boundaries are determined by:
 * - Whitespace in normal state
 * - Special characters in normal state
 * - Operators (2-char sequences)
 *
 * Handles:
 * - Quoted strings as single tokens
 * - Escaped characters
 * - Special shell operators
 *
 * @param input String to analyze
 * @return Length of next token
 *
 * @note Returns 2 for two-character operators
 * @note Returns 1 for single-character operators
 * @see is_special_char() for operator detection
 * @see is_operator() for two-char operator detection
 */
size_t	get_token_length_with_state(const char *input)
{
	size_t				len;
	t_tokeniser_state	state;

	len = 0;
	state = STATE_NORMAL;
	while (input[len])
	{
		state = get_next_state(state, input[len]);
		if (state == STATE_NORMAL && \
			ft_isspace(input[len]) && len > 0)
			break ;
		if (state == STATE_NORMAL && len == 0 \
			&& is_special_char(input[len]))
		{
			if (is_operator(input))
				return (2);
			return (1);
		}
		if (state == STATE_NORMAL && len > 0 \
			&& is_special_char(input[len]))
			break ;
		len++;
	}
	return (len);
}

/**
 * @brief Extracts token from input string handling quotes and escapes
 *
 * Extraction process:
 * 1. Allocates space for token
 * 2. Copies characters while tracking state
 * 3. Handles escaped characters
 * 4. Removes quotes from final token
 *
 * @param input Input string to extract from
 * @param len   Length of token to extract
 * @return Newly allocated string containing token, or NULL on allocation failure
 *
 * @note Caller must free returned string
 * @note Backslash characters are removed from output
 * @see get_next_state() for state tracking
 */
char	*extract_token(const char *input, size_t len)
{
	char				*result;
	size_t				i;
	size_t				j;
	t_tokenizer_state	state;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	state = STATE_NORMAL;
	while (i < len)
	{
		state = get_next_state(state, input[i]);
		if (state != STATE_IN_BACKSLASH)
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
