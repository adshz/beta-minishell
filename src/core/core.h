/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:57:55 by szhong            #+#    #+#             */
/*   Updated: 2025/01/16 15:58:16 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CORE_H
# define CORE_H
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

bool	parse_and_build_ast(t_shell *shell);
void	interactive_loop(t_shell *shell);
#endif
