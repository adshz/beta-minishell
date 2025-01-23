/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:31:16 by szhong            #+#    #+#             */
/*   Updated: 2025/01/22 19:20:52 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HASHTABLE_H
# define HASHTABLE_H
# define HASH_SIZE 1024

# include "libft.h"
# include <stdlib.h>

/* Hash Table - Hash Item Structure */
/**
 * @brief Hash Table Item Structure
 *
 * Represents a single key-value pair in the hash table,
 * with support for collision resolution through chaining
 *
 * @param key	Environment variable name (e.g., "PATH", "HOME")
 * @param value	Environment variable value (e.g., "/usr/bin:/bin")
 * @param next	Pointer to next item in case of hash collision
*/
typedef struct s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
}	t_hash_item;


/* Hash Table Structure */
/*
 * @breif Hash table structure for environment variables
 *
 * Manges environment variables using a hash table implementation.
 * Provides O(1) average case access time for variable lookups
 *
 * @param items Array of hash item pointers (the hash table buckets)
 * @param size	Number of buckets in the hash table
 * @param count	Number of items currently stored in the table
 */

typedef struct s_hashmap
{
	t_hash_item	**items;
	size_t		size;
	size_t		count;
}	t_hash_map;

#endif
