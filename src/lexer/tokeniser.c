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

/**
 * @brief Adds a new token to the end of token list
 *
 * Maintains the linked list structure of tokens by:
 * - Handling empty list case (head is NULL)
 * - Traversing to end of existing list
 * - Attaching new token
 *
 * @param head      Current head of token list
 * @param new_token Token to add to the list
 * @return Updated head of token list, or NULL on failure
 *
 * @note Safe to call with NULL head (creates new list)
 * @note Returns NULL if new_token is NULL
 */
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

/**
 * @brief Creates a single token from input string
 *
 * Process:
 * 1. Extracts token value from input
 * 2. Determines token type
 * 3. Creates token structure
 *
 * @param input Input string to process
 * @param len   Length of token to extract
 * @return New token structure, or NULL on failure
 *
 * @note Handles memory cleanup on failure
 * @note Returns NULL for EOF tokens
 * @see extract_token() for token value extraction
 * @see get_token_type() for token type determination
 */
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

/**
 * @brief Advances input pointer past whitespace characters
 *
 * Used to prepare input for token extraction by skipping:
 * - Spaces
 * - Tabs
 * - Newlines
 * - Other whitespace characters
 *
 * @param input String to process
 * @return Pointer to first non-whitespace character
 *
 * @note Safe to call with NULL input
 * @see ft_isspace() for whitespace determination
 */
static const char	*skip_whitespace(const char *input)
{
	while (input && ft_isspace(*input))
		input++;
	return (input);
}

/**
 * @brief Tokenizes input string into linked list of tokens
 *
 * Main tokenization process:
 * 1. Skips whitespace
 * 2. Determines token length
 * 3. Processes individual tokens
 * 4. Builds token list
 *
 * Used by the parser to break command line into processable tokens
 * for AST construction.
 *
 * @param input Command line string to tokenize
 * @return Head of token list, or NULL on failure
 *
 * @note Handles memory cleanup on any failure
 * @note Returns NULL for empty input
 * @see process_single_token() for individual token creation
 * @see add_token_to_list() for list building
 *
 * Example token sequence:
 * "ls -l | grep foo" becomes:
 * WORD(ls) -> OPTION(-l) -> PIPE(|) -> WORD(grep) -> WORD(foo)
 */
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
