/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:43 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 17:16:35 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TYPES_H
# define TYPES_H
# include <stdbool.h>
# include <termios.h>
# include <sys/types.h>
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

/*########################################*/

/* Token Structure*/
/**
 * @brief Token structure for lexical analysis
 *
 * Represents a single token in the input stream, storing its value
 * type, and link to the next token in the sequence.
 *
 * @param value	Actual string content of the token (e.g. command name, flag)
 * @param type	Type classification of token (e.g. TOKEN_WORD, TOKEN_PIPE..)
 * @param next	Pointer to next token in the sequence, NULL if last token
*/
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

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


/*
 * Environment Structure
*/
// typedef struct s_env
// {
// 	char	*key;
// 	char	*value;
// 	struct s_env	*next;
// }	t_env;

// use t_hash_item as t_env
typedef t_hash_item t_env;


/* Shell Structure */
/**
 * @brief Main shell structure holding program data
 * 
 * The struct contains all essential components for program operations
 * such as command parsing data, execution state, environement management
 * process tracking, and terminal settings.
 * 
 * @param line				Current user command line being parsered by parser
 * @param tokens			List of tokens by scanner and lexer (lexcial analysis)
 * @param ast				Abstract syntax tree representing commands, flags etc
 * @param env				Environment variables stored by Hash Table
 * @param cmds				History of executed commands using linked list
 * @param pid				Process ID of the shell
 * @param pids				Array of child process IDs
 * @param old_pwd			Previous working directory path
 * @param history			Array of command history entries
 * @param exit_status		Exit status of the last executed command
 * @param stdin_backup		Backup of standard input file descriptor
 * @param stdout_backup		Backup of stadnard output file descriptor
 * @param term_settings		Terminal configuration settings
 * @param heredoc_sigint	Flag indicating heredoc interrupt state
 * @param signint_child		Flag indicating child process interrupt state
 * @param in_pipe			Flag indicating if currently in a pipeline
*/
typedef struct s_shell
{
	char			*line;
	t_token			*tokens;
	t_ast_node		*ast;
	t_hashmap		*env;
	t_list			*cmds;
	pid_t			pid;
	pid_t			*pids;
	char			*old_pwd;
	char			**history;
	int				exit_status;
	int				stdin_backup;
	int				stdout_backup;
	bool			heredoc_sigint;
	bool			signint_child;
	bool			in_pipe;
	struct termios	term_settings;
}	t_shell;
#endif
