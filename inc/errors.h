/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:11 by szhong            #+#    #+#             */
/*   Updated: 2025/01/23 15:58:32 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ERRORS_H
# define ERRORS_H
# define SUCCESS 0
# define ERROR 1

/* Errors Types */
/**
 * @brief Error types enumeration for shell erro handling
 *
 * Defines all possible error types that could occur during shell operation
 * Used for consistent error reporting and handling across the program.
 *
 * @param ERR_NONE			No error occurred (SUCCESS)
 * @param ERR_MALLOC		Memory allocation failure
 * @param ERR_SYNTAX		Command syntax error
 * @param ERR_CMD_NOT_FOUND	Command not found in PATH variable
 * @param ERR_PERMISSION	Permission denied accessing file/directory
 * @param ERR_PIPE			Pipe creation or handling failure
 * @param ERR_FORK			Process forking failure
 * @param ERR_DUP			File descriptor duplication failure
 * @param ERR_EXEC			Command execution failure
 * @param ERR_ENV			Environment variable operation failure
*/
typedef enum e_rror_type
{
	ERR_NONE,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_PERMISSION,
	ERR_FILE_NOT_FOUND,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP,
	ERR_EXEC,
	ERR_ENV
}	t_error_type;

#endif
