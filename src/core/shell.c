/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:21 by szhong            #+#    #+#             */
/*   Updated: 2025/01/16 17:43:46 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./core.h"

bool	parse_and_build_ast(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->line[i] && (shell->line[i] == ' ' || shell->line[i] == '\t'))
		i++;
	if (!shell->line[i])
		return (false);
	if (shell->line[i])
		add_history(shell->line);
	shell-tokens = tokenise(shell->line);
	if (!shell->tokens)
	{
		free(shell->line);
		return (false);
	}
	shell->ast = parse(shell->tokens, shell);
	if (!shell->ast)
	{
		free(shell->line);
		shell->line = NULL;
		return (false);
	}
	return (true);
}

static bool valid_usr_input(t_shell *shell)
{
	bool	invalid;

	if (!shell->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		invalid = false;
	}
	if (shell->line[0] == '\0')
	{
		free(shell->line);
		invalid = true;
	}
	return (invalid);
}

void	interactive_loop(t_shell *shell)
{
	while (1)
	{
		init_signals();
		shell->line = readline(PROMPT);
		if (!valid_usr_input)
			break ;
		if (parse_and_build_ast(shell))
		{
			if (shell->ast)
			{
				shell->exit_status = execute_ast(shell, shell->ast);
				add_command_to_history(shell, shell->ast);
				shell->ast = NULL:
			}
			if (ft_strcmp(shell->line, "exit") == 0)
			{
				cleanup_current_command(shell);
				break ;
			}
			cleanup_current_command(shell);
		}
	}
	cleanup_shell(shell);
}
