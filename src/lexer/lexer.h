/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:09:24 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:01:11 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include "libft.h"

/* Tokeniser States */
/**
 * @brief Tokensier state especial for quote and escape handling 
 *
 * Tracks the current parsing state during tokenisation, particularly
 * for handling quoted strings and escaped characters correctly.
 *
 * @param STATE_NORMAL			Default state, processing regular input
 * @param STATE_IN_SINGLE_QUOTE	Inside single quotes, everything as literal
 * @param STATE_IN_DOUBLE_QUOTE	Inside double quotes, variables can be expanded
 * @param STATE_IN_BACKSLASH	After backslash, escaping next character
*/
typedef enum e_tokeniser_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_BACKSLASH
}	t_tokeniser_state;

/* Token types */
/**
 * @brief Token types for lexcial analysis
 *
 * Defines all possible token types that can be identified during
 * command line tokensiation. Used by the lexer to classify input compoents
 *
 * @param TOKEN_WORD			Words, command names, arguments, filenames
 * @param TOKEN_PIPE			Pipe operator (|)
 * @param TOKEN_REDIRECT_IN		Input redirection operator (<)
 * @param TOKEN_REDIRECT_OUT	Output redirection operator (>)
 * @param TOKEN_APPEND			Append redirection operator (>>)
 * @param TOKEN_HEREDOC			Here document operator (<<)
 * @param TOKEN_AND				Logical AND operator (&&)
 * @param TOKEN_OR				Logical OR operator (||)
 * @param TOKEN_SEMICOLON		Command separator operator (;)
 * @param TOKEN_NEWLINE			Newline character (\n)
 * @param TOKEN_EOF				End of input marker. 
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMICOLON,
	TOKEN_NEWLINE,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;


#endif
