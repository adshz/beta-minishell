/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:20:21 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 16:20:23 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

int	check_input_file(const char *filename)
{
	if (access(filename, F_OK) == -1)
		return (0);
	if (access(filename, R_OK) == -1)
		return (0);
	return (1);
}

bool	validate_file_token(t_token *file_token)
{
	if (!file_token || file_token->type != TOKEN_WORD)
	{
		ft_putendl_fd(\
				"minishell: syntax error near unexpected token `newline'", \
				STDERR_FILENO);
		return (false);
	}
	return (true);
}

t_ast_node	*create_file_node(t_token *file_token, \
								t_ast_node *redir_node)
{
	t_ast_node	*file_node;

	file_node = create_ast_node(AST_COMMAND, file_token->value);
	if (!file_node)
	{
		free_ast(redir_node);
		return (NULL);
	}
	return (track_ast_node(file_node));
}

bool	is_redirection_type(t_ast_type type)
{
	return (type == AST_REDIR_IN || \
			type == AST_REDIR_OUT || \
			type == AST_REDIR_APPEND || \
			type == AST_HEREDOC);
}
