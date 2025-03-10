/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:24:04 by evmouka           #+#    #+#             */
/*   Updated: 2025/02/13 23:25:07 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "shell.h"
# include "errors.h"

/* Error handling */
int		extern_handle_fork_error(char *cmd_path, char **env_array);
void	extern_cleanup_resources(char *cmd_path, char **env_array);
void	cleanup_and_exit_external(t_shell *shell, int status);
void	cleanup_command_resources(t_shell *shell);
void	cleanup_ast_by_type(t_list *node_list);
void	cleanup_ast_node(t_ast_node *node);
void	handle_error(t_shell *shell, t_error_type error, const char *detail);
void	cleanup_heredoc_signal_interrupt(t_ast_node *node);
/* Cleanup functions */
void	cleanup_shell(t_shell *shell);
void	cleanup_current_command(t_shell *shell);
void	cleanup_env_and_cmds(t_shell *shell);
void	free_history(char **history);
void	cleanup_terminal_state(t_shell *shell);
void	cleanup_process_state(t_shell *shell);
/* String utilities */
void	free_string_array(char **array);
char	*join_strings(const char *s1, const char *s2);
void	ft_free_array(char **array);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
/* Error handling */
int		print_error(char *cmd, char *msg, int error_code);
void	free_cmd(void *content);
void	add_command_to_history(t_shell *shell, t_ast_node *cmd);
bool	is_only_whitespace(const char *str);
void	cleanup_ast_node_data(t_ast_node *node);
/* Memory-tracked string functions */
char	*tracked_strdup(const char *s);
char	*tracked_itoa(int n);
t_list	*tracked_lstnew(void *content);
#endif
