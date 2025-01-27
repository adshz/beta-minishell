/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:49:24 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:50:54 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H
# include "libft.h"

/* Abstract Syntax Tree Node Types */
/**
 * @brief AST Node types for the shell's command parser
 *
 * Defines all possible types of nodes in the Abstract Syntax Tree
 * Used to represent different command components and operators
 *
 * @param AST_COMMAND		Simple command node (e.g., "ls", "echo" etc)
 * @param AST_PIPE			Pipe operator node (|)
 * @param AST_REDIR_IN		Input redirection node (<)
 * @param AST_REDIR_OUT		Output redirection node (>)
 * @param AST_REDIR_APPEND	Append redirection node (>>)
 * @param AST_HEREDOC		Here document node (<<)
 * @param AST_AND			Logical AND operator node (&&)
 * @param AST_OR			Logical OR operator node (||)
 * @param AST_VAR_EXPANSION	Variable expansion node ($VAR)
*/
typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_REDIR_APPEND,
	AST_HEREDOC,
	AST_AND,
	AST_OR,
	AST_VAR_EXPANSION
}	t_ast_type;

/* AST Node Structure */
/**
 * @brief Abstract Syntax Tree Node Structutre
 *
 * Represents a node in the AST, containing command information
 * variable expansion status, and binary tree links
 *
 * @param type		Node type (AST_COMMAND, AST_PIPE, AST_REDIR_IN, etc.)
 * @param value		Primary value (command name or filename for redirections)
 * @param args		Array of command arguments, NULL terminated
 * @param is_expanded	Flag indicating if node contains epanded variables
 * @param original		Original string before variable expansions
 * @param left			Left child node (e.g., represents command before pipe)
 * @param right			Right child node (e.g, represents command after pipe)
*/
typedef struct s_ast_node
{
	t_ast_type			type;
	char				*value;
	char				**args;
	int					is_expanded;
	char				*original;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;
#endif
