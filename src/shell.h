/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:16:04 by szhong            #+#    #+#             */
/*   Updated: 2025/01/16 15:17:20 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHELL_H
# define SHELL_H
# define PROMPT "minishell$ "
# include "libft.h"
# include "./core/core.h"

void	init_shell(t_shell *shell, char *argv[], char *envp[]);
void	cleanup_shell(t_shell *shell);
void	free_history(char **history);
#endif
