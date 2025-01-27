/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:57:55 by szhong            #+#    #+#             */
/*   Updated: 2025/01/21 17:04:58 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file core.h
 * @brief Core functionality for the minishell program
 *
 * This header defines the core functions responsible for:
 * - Shell initialization and cleanup
 * - Command parsing and AST building
 * - Interactive shell loop
 * - Signal handling
 */
#ifndef CORE_H
# define CORE_H
# include "shell.h"

/* Core structure initialisation */
/**
 * @brief Initializes the shell structure and environment
 *
 * @param shell Pointer to shell structure to initialize
 * @param argv  Array of command line arguments
 * @param envp  Array of environment variables
 * @return SUCCESS if initialization succeeds, ERROR otherwise
 */
int		init_shell(t_shell *shell, char *argv[], char *envp[]);

/* AST building and parsing */
/**
 * @brief Parses command line and builds abstract syntax tree
 *
 * @param shell Pointer to shell structure
 * @return true if parsing and AST building succeed, false otherwise
 */
bool	parse_and_build_ast(t_shell *shell);

/**
 * @brief Main shell interactive loop
 *
 * Handles:
 * - Reading user input
 * - Parsing commands
 * - Executing commands
 * - Managing command history
 *
 * @param shell Pointer to shell structure
 */
void	interactive_loop(t_shell *shell);

/* Signal handling */
/**
 * @brief Initializes signal handlers for the shell
 *
 * Sets up handlers for:
 * - SIGINT (Ctrl+C)
 * - SIGQUIT (Ctrl+\)
 * - Other relevant signals
 */
void	init_signals(void);

#endif
