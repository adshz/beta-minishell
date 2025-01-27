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
#include "core.h"
#include "shell.h"

/**
 * @brief Checks if a line contains only whitespace characters
 *
 * @param line String to check
 * @return true if line is empty or contains only whitespace,
 *         false otherwise
 */
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

/**
 * @brief Builds abstract syntax tree from command line
 *
 * Process:
 * 1. Tokenizs the input line
 * 2. Parses tokens into AST
 *
 * @param shell Pointer to shell structure
 * @return true if AST built successfully, false on error
 *
 * @note Frees line on tokenization failure
 */
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

/**
 * @brief Parses command line and builds AST
 *
 * Process:
 * 1. Validates input line
 * 2. Adds command to history
 * 3. Builds AST from input
 *
 * @param shell Pointer to shell structure
 * @return true if parsing succeeds, false otherwise
 *
 * @note Handles memory cleanup on failure
 */
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

/**
 * @brief Validates user input for shell processing
 *
 * Checks for:
 * - NULL input (EOF/Ctrl+D): Prints "exit" and returns false
 * - Empty line: Frees line and returns false
 *
 * @param shell Pointer to shell structure
 * @return true if input is valid for processing, false if shell should exit
 *         or skip processing
 *
 * @note readline() returns NULL on Ctrl+D (EOF) or error
 */
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

/**
 * @brief Main interactive shell loop
 *
 * Process flow:
 * 1. Initialize signals
 * 2. Read user input
 * 3. Parse and build AST
 * 4. Execute commands
 * 5. Update history
 * 6. Cleanup
 *
 * @param shell Pointer to shell structure
 *
 * @note Continues until EOF or exit command
 */
void	interactive_loop(t_shell *shell)
{
	while (1)
	{
		init_signals();
		shell->line = readline(PROMPT);
		if (!valid_usr_input(shell))
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
