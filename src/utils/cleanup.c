/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:56:47 by szhong            #+#    #+#             */
/*   Updated: 2025/02/13 21:49:44 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/utils.h"

static void	cleanup_command_resources(t_shell *shell)
{
	static bool	in_final_cleanup;

	in_final_cleanup = false;
	if (!in_final_cleanup && (shell->ast || shell->tokens || shell->line))
	{
		cleanup_current_command(shell);
	}
	if (shell->cmds)
	{
		if (!in_final_cleanup)
		{
			if (shell->ast == NULL)
			{
				t_list *current = shell->cmds;
				t_list *next;
				while (current)
				{
					next = current->next;
					free(current);
					current = next;
				}
			}
			else
				ft_lstclear(&shell->cmds, &free_cmd);
		}
		shell->cmds = NULL;
	}
	if (!in_final_cleanup)
		in_final_cleanup = true;
}

static void	cleanup_environment_resources(t_shell *shell)
{
	cleanup_process_state(shell);
	cleanup_env_cache(shell);
	if (shell->env)
	{
		hashmap_destroy(shell->env);
		shell->env = NULL;
	}
}

static void	cleanup_history_resources(t_shell *shell)
{
	clear_history();
	rl_clear_history();
	if (shell->history)
	{
		free_history(shell->history);
		shell->history = NULL;
	}
}

static void	cleanup_file_descriptors(t_shell *shell)
{
	shell->stdin_backup = STDIN_FILENO;
	shell->stdout_backup = STDOUT_FILENO;
	cleanup_fds();
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_file_descriptors(shell);
	cleanup_command_resources(shell);
	cleanup_environment_resources(shell);
	cleanup_history_resources(shell);
	ft_heredoc_memory_collector(NULL, true);
	ft_hash_memory_collector(NULL, true);
	cleanup_export_values();
	cleanup_expanded_strings();
	cleanup_pipeline_nodes();
}
