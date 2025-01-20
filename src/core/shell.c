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

static bool	is_empty_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (true);
	return (false);
}

static bool	build_ast_tree(t_shell *shell)
{
	shell->tokens = tokenise(shell->line);
	if (!shell->tokens)
	{
		ft_putendl_fd("minishell: tokenisation failed", STDERR_FILENO);
		free(shell->line);
		return (false);
	}
	shell->ast = parse(shell->tokens, shell);
	if (shell->ast != NULL)
		return (true);
	return (false);
}

bool	parse_and_build_ast(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (!shell->line || is_empty_line(shell->line))
	{
		free(shell->line);
		shell->line = NULL;
		return (false);
	}
	add_history(shell->line);
	if (!build_ast_tree(shell))
	{
		free(shell->line);
		shell->line = NULL;
		return (false);
	}
	return (true);
}

static bool	valid_usr_input(t_shell *shell)
{
	if (!shell->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (false);
	}
	if (shell->line[0] == '\0')
	{
		free(shell->line);
		return (false);
	}
	return (true);
}

void	interactive_loop(t_shell *shell)
{
	while (1)
	{
		init_signals();
		shell->line = readline(PROMPT);
		if (!valid_usr_input)
			break ;
		if (!parse_and_build_ast(shell))
			continue ;
		if (shell->ast)
		{
			shell->exit_status = execute_ast(shell, shell->ast);
			add_command_history(shell, shell->ast);
			shell->ast = NULL;
		}
		cleanup_current_command(shell);
	}
	cleanup_shell(shell);
}
