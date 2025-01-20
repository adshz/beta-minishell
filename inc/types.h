/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:43 by szhong            #+#    #+#             */
/*   Updated: 2025/01/20 17:21:16 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <termios.h>
# include <sys/types.h>
# include "libft.h"

/*
 * Token types
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


/*
 * AST Node Types
*/
typedef enum e_ast_type
{

}
#endif
