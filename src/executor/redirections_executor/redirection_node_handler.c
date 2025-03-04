/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_node_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:48:35 by szhong            #+#    #+#             */
/*   Updated: 2025/02/18 00:48:46 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../executor.h"

static void	collect_nodes_into_temp(t_ast_node *current, \
								t_ast_node *temp_nodes[], \
								int *temp_count)
{
	while (current && *temp_count < 100)
	{
		if (current->type == AST_REDIR_IN || current->type == AST_REDIR_OUT || \
			current->type == AST_REDIR_APPEND || current->type == AST_HEREDOC)
		{
			temp_nodes[*temp_count] = current;
			(*temp_count)++;
		}
		current = current->left;
	}
}

static void	reverse_nodes_order(t_ast_node *temp_nodes[], \
							t_ast_node *redir_nodes[], \
							int temp_count, \
							int *redir_count)
{
	int	i;

	i = temp_count - 1;
	while (i >= 0)
	{
		redir_nodes[*redir_count] = temp_nodes[i];
		(*redir_count)++;
		i--;
	}
}

int	collect_redirection_nodes(t_ast_node *node, t_ast_node *redir_nodes[], \
							int *redir_count)
{
	t_ast_node	*temp_nodes[100];
	int			temp_count;

	temp_count = 0;
	*redir_count = 0;
	collect_nodes_into_temp(node, temp_nodes, &temp_count);
	reverse_nodes_order(temp_nodes, redir_nodes, temp_count, redir_count);
	return (0);
}

int	handle_redirection_type(t_ast_node *current, t_shell *shell, \
							int saved_stdin, int saved_stdout)
{
	int	status;

	status = 0;
	if (current->type == AST_REDIR_OUT)
		status = handle_output_redirection(current, shell);
	else if (current->type == AST_REDIR_APPEND)
		status = handle_append_redirection(current, shell);
	else if (current->type == AST_REDIR_IN)
		status = handle_input_redirection(current, shell);
	else if (current->type == AST_HEREDOC)
		status = handle_heredoc(current, shell);
	if (status != 0)
		cleanup_and_exit(saved_stdin, saved_stdout, status);
	return (status);
}
