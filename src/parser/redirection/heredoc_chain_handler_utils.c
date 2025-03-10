/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_chain_handler_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:01:22 by szhong            #+#    #+#             */
/*   Updated: 2025/02/21 10:02:39 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

static void	unlink_command_node(t_ast_node *first_redir, \
								t_ast_node *command_node)
{
	t_ast_node	*current;

	current = first_redir;
	while (current)
	{
		if (current->left == command_node)
		{
			current->left = NULL;
			break ;
		}
		current = current->left;
	}
}

static void	free_redir_node_content(t_ast_node *current)
{
	if (current->right)
	{
		if (current->right->value)
			ft_heredoc_memory_delone(current->right->value);
		if (current->right->args)
			ft_free_array(current->right->args);
		if (current->right->original)
			ft_heredoc_memory_delone(current->right->original);
		if (current->right->type == AST_HEREDOC)
			ft_heredoc_memory_delone(current->right);
		else
			free(current->right);
	}
	if (current->value)
		ft_heredoc_memory_delone(current->value);
	if (current->args)
		ft_free_array(current->args);
	if (current->data.content_path)
		ft_heredoc_memory_delone(current->data.content_path);
	if (current->original)
		ft_heredoc_memory_delone(current->original);
	if (current->data.delimiter)
		ft_heredoc_memory_delone((void *)current->data.delimiter);
}

t_ast_node	*cleanup_heredoc_nodes(t_ast_node *first_redir, \
										t_ast_node *command_node)
{
	t_ast_node	*current;
	t_ast_node	*next;

	current = NULL;
	next = NULL;
	if (first_redir)
	{
		unlink_command_node(first_redir, command_node);
		current = first_redir;
		while (current)
		{
			next = current->left;
			free_redir_node_content(current);
			if (current->type == AST_HEREDOC)
				ft_heredoc_memory_delone(current);
			else
				free(current);
			current = next;
		}
	}
	if (command_node)
		free_ast(command_node);
	return (NULL);
}
