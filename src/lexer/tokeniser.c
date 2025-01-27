/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:09:49 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 17:57:54 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

static t_token	*add_token_to_list(t_token *head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (NULL);
	if (!head)
		return (new_token);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (head);
}

static t_token	*process_single_token(const char *input, size_t len)
{
	char			*value;
	t_token			*new_token;
	t_token_type	*type;

	value = extract_token(input, len);
	if (!value)
		return (NULL);
	type = get_token_type(value);
	if (type == TOKEN_EOF)
	{
		free(value);
		return (NULL);
	}
	new_token = create_token(type, value);
	free(value);
	return (new_token);
}

static const char	*skip_whitespace(const char *input)
{
	while (input && ft_isspace(*input))
		input++;
	return (input);
}

t_token	*tokenise(const char *input)
{
	t_token	*head;
	t_token	*new_token;
	size_t	len;

	head = NULL;
	while (input && *input)
	{
		input = skip_whitespace(input);
		if (!*input)
			break ;
		len = get_token_length_with_state(input);
		if (len == 0)
			break ;
		new_token = process_single_token(input, len);
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		head = add_token_to_list(head, new_token);
		if (!head)
			return (NULL);
		input += len;
	}
	return (head);
}
