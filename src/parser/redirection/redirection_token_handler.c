/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:41:37 by szhong            #+#    #+#             */
/*   Updated: 2025/02/19 17:42:05 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser/parser.h"

static void	init_redir_token(t_redir_token *rt, t_redir_parse *parse,
							t_token **tokens)
{
	rt->current = &parse->current;
	rt->tokens = tokens;
	rt->next_token = NULL;
	rt->result_left_node = parse->result_left_node;
	rt->output_node = NULL;
	rt->prev_type = parse->prev_type;
	rt->shell = parse->shell;
}

/**
 * @brief Handles the redirection token
 *
 * This function handles the redirection token.
 * It either handles the heredoc token or the regular redirection token.
 * @note
 * well we have 2 kinds of redirection tokens:
 * - heredoc token (e.g. `<<`)
 * - regular redirection token (e.g. `>`, `>>`, `<`)

 */
static t_ast_node	*handle_redirection_token(t_redir_token *rt)
{
	if ((*rt->current)->type == TOKEN_HEREDOC)
		return (handle_heredoc_token(rt));
	return (handle_regular_redirection(rt));
}

/**
 * @brief Processes the redirection token
 *
 * This function processes the redirection token.
 * It either handles the word token or the redirection token.
 * @note
 * there are if -else, so we first handle word token
 * then we handle the redirection token
 * as its parent function parse_redirection_construct() has a while loop
 * iterate through each token in the tokens list
 */
t_ast_node	*process_redir_token(t_redir_parse *parse, t_token **tokens)
{
	t_word_token	wt;
	t_redir_token	rt;

	if (parse->current->type == TOKEN_WORD)
	{
		init_word_token(&wt, parse, tokens);
		parse->result_left_node = handle_word_token(&wt);
	}
	else if (is_redirection_token(parse->current->type))
	{
		init_redir_token(&rt, parse, tokens);
		parse->result_left_node = handle_redirection_token(&rt);
	}
	if (!parse->result_left_node)
	{
		parse->shell->exit_status = 258;
		return (NULL);
	}
	return (parse->result_left_node);
}
