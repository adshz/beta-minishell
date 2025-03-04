#include "parser/parser.h"

/**
 * @brief Handles the regular redirection token
 *
 * This function handles the regular redirection token.
 * It processes the redirection and returns the output node.
 *
 * @note
 * as for the case of `echo hello> file.txt`,
 * tokens are
 * - echo (TOKEN_WORD)
 * - hello (TOKEN_WORD)
 * - > (TOKEN_REDIRECT_OUT)
 * - file.txt (TOKEN_WORD)
 *
 * *rt->current points to regular redirection token
 * - > (TOKEN_REDIRECT_OUT)
 * - >> (TOKEN_REDIRECT_APPEND)
 * - < (TOKEN_REDIRECT_IN)
 *
 * case `echo hello > file.txt`
 * rt->result_left_node is the command before the redirection token
 * which is `echo hello`
 *
 * rt->output_node is the output node of the redirection
 * which is `file.txt`
 *
 * rt->prev_type is the previous token type
 * which is TOKEN_EOF
 *
 * rt->shell is the shell instance
 *
 * First of all, t_token **current, t_token **tokens are double pointers
 * tokens tracks the overall token stream position
 * current is used for local navigation within the current parsing context
 * example: echo hello > file.txt
 * When we are in the function call, our
 * - *rt->current points to ">" (Token 3) because it's following parse->current
 * - *rt->tokens points to ">" (Token 3) because it didn't move, points
 * to the same as *rt->current
 *
 * go through rt->output_node = process_redirection();
 * - rt->prev_type  // Store TOKEN_REDIRECT_OUT
 * // Skip both ">" and "file.txt"
 * - *rt->tokens = (*rt->current)->next->next;  // Now points to Token 5 (NULL)
 * // Sync current with tokens
 * - *rt->current = *rt->tokens; // Now points to Token 5 (NULL)
 */
static t_ast_node *process_command_after_redirection(t_redir_token *rt, 
                                                   t_token *next_after_redir)
{
	t_ast_node *cmd_node;
	t_ast_node *output_node;

	cmd_node = track_ast_node(create_ast_node(AST_COMMAND, next_after_redir->value));
	if (!cmd_node)
		return (NULL);

	output_node = process_redirection(*rt->current, cmd_node);
	if (!output_node)
	{
		free_ast(cmd_node);
		rt->shell->exit_status = 258;
		return (NULL);
	}
	*rt->tokens = next_after_redir->next;
	return (output_node);
}

static t_ast_node *process_existing_command(t_redir_token *rt, 
                                          t_token *next_after_redir)
{
	t_ast_node *output_node;

	output_node = process_redirection(*rt->current, rt->result_left_node);
	if (!output_node)
	{
		rt->shell->exit_status = 258;
		return (NULL);
	}
	*rt->tokens = next_after_redir;
	return (output_node);
}

static t_ast_node *process_normal_redirection(t_redir_token *rt, 
                                            t_token *next_after_redir)
{
	t_ast_node *output_node;

	if (!rt->result_left_node)
	{
		rt->result_left_node = track_ast_node(create_ast_node(AST_COMMAND, NULL));
		if (!rt->result_left_node)
			return (NULL);
	}
	output_node = process_redirection(*rt->current, rt->result_left_node);
	if (!output_node)
	{
		rt->shell->exit_status = 258;
		return (NULL);
	}
	*rt->tokens = next_after_redir;
	return (output_node);
}

t_ast_node *handle_regular_redirection(t_redir_token *rt)
{
	t_ast_node *output_node;
	t_token *next_after_redir;

	output_node = NULL;
	next_after_redir = (*rt->current)->next->next;
	if (next_after_redir && next_after_redir->type == TOKEN_WORD &&
		!is_redirection_token(next_after_redir->type))
		output_node = process_command_after_redirection(rt, next_after_redir);
	else if (rt->result_left_node && rt->result_left_node->left &&
			 rt->result_left_node->left->type == AST_COMMAND)
		output_node = process_existing_command(rt, next_after_redir);
	else
		output_node = process_normal_redirection(rt, next_after_redir);
	if (output_node)
	{
		rt->prev_type = (*rt->current)->type;
		*rt->current = *rt->tokens;
	}
	return (output_node);
}