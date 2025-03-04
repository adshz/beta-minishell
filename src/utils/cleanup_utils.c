/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:56:31 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 15:58:11 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/utils.h"

void	cleanup_command_resources(t_shell *shell)
{
	static bool	in_final_cleanup;
	t_list		*current;
	t_list		*next;

	in_final_cleanup = false;
	if (!in_final_cleanup && (shell->ast || shell->tokens || shell->line))
		cleanup_current_command(shell);
	if (shell->cmds)
	{
		if (!in_final_cleanup)
		{
			if (shell->ast == NULL)
			{
				current = shell->cmds;
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

void	cleanup_ast_by_type(t_list *node_list)
{
	t_list		*current;
	t_list		*next;
	t_ast_node	*ast_node;

	current = node_list;
	while (current)
	{
		next = current->next;
		ast_node = current->content;
		if (ast_node && !ast_node->is_freed)
		{
			if (ast_node->type == AST_PIPE)
				cleanup_pipeline_nodes();
			else
				free_ast(ast_node);
		}
		free(current);
		current = next;
	}
}
