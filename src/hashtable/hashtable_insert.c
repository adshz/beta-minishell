/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:51:48 by szhong            #+#    #+#             */
/*   Updated: 2025/01/23 16:55:03 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "hashtable.h"
#include "errors.h"

static t_hash_item	*create_new_item(char *key, char *value)
{
	t_hash_item	*new_item;
	char		*new_key;
	char		*new_value;

	new_item = (t_hash_item *)malloc(sizeof(t_hash_item));
	if (!new_item)
		return (NULL);
	new_key = ft_strdup(key);
	new_value = ft_strdup(value);
	if (!new_key || !new_value)
	{
		free(new_key);
		free(new_value);
		free(new_item);
	}
	new_item->key = new_key;
	new_item->value = new_value;
	new_item->next = NULL;
	return (new_item);
}

static t_hash_item	*find_existing_item(t_hashmap *table, char *key, size_t index)
{
	t_hash_item	*item;

	item = table->items[index];
	while (item)
	{
		if (ft_strcmp(item->key, key) == 0)
			return (item);
		item = item->next;
	}
	return (NULL);
}

static int	update_existing_item(t_hash_item *item, char *value, int free_old)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (free_old)
		free(item->value);
	item->value = new_value;
	return (0);
}

int	hashmap_insert(t_hashmap *table, char *key, char *value, int free_old)
{
	size_t		index;
	t_hash_item	*existing;
	t_hash_item	*new_item;

	if (!table || !key || !value)
		return (ERROR);
	index = hash_function(key, table->size);
	existing = find_existing_item(table, key, index);
	if (existing)
		return (update_existing_item(existing, value, free_old));
	new_item = create_new_item(key, value);
	if (!new_item)
		return (ERROR);
	new_item->next = table->item[index];
	table->items[index] = new_item;
	return (SUCCESS);
}
