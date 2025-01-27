/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:39:38 by szhong            #+#    #+#             */
/*   Updated: 2025/01/27 15:43:35 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "hashtable.h"

static void	free_hashitem(t_hash_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	hashmap_remove(t_hashmap *table, const char *key)
{
	size_t		idx;
	t_hash_item	*current;
	t_hash_item	*prev;

	if (!table || !key)
		return ;
	idx = hash_function(key, table->size);
	current = table->items[idx];
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				table->items[idx] = current->next;
			free_hashitem(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
