/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:43 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 18:55:47 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TYPES_H
# define TYPES_H
# include <stdbool.h>
# include <termios.h>
# include <sys/types.h>
# include "libft.h"


/*########################################*/


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
