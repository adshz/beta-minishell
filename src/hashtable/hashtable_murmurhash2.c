/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_murmurhash2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:22:22 by szhong            #+#    #+#             */
/*   Updated: 2025/01/24 17:05:57 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "hashtable.h"
#include <stdlib.h>

/**
 * @brief Processes a chunk of data in the MurmurHash algorithm
 *
 * Applies the MurmurHash mixing function to a single chunk:
 *   1. Multiply by the hash multiplier
 *   2. XOR with right-shifted value
 *   3. Multiply again for better bit mixing
 *
 * @param chunk Pointer to the chunk being processed
 * @param multiplier The MurmurHash magic constant (0x5bd1e995)
 * @param rotation_bits Number of bits for right rotation (typically 24)
 *
 * @note This is part of the MurmurHash2 algorithm; a step of hashing a key to
 * index
 * @par
 * "mixing" (混合) means a process of using mathematical operations (here we
 * have multiplicaton and XOR) to rearrange and combine the bits of data 
 * (打乱数据的原始结构) in a way we can have more random and uniformed
 * distribution of the hash function
 *   - Step 1: we multiply it with a magic constant (0x5bd1e995) 
 *   - Step 2: we do XOR operation with a right-shifted versrion of itself to
 *   further mix the data
 *   - Step 3: we do another multiplifcation to further mix the bits
 * @see hash_function() for the complete hashing process
 */
static void	process_chunk(unsigned int *chunk, \
						unsigned int multiplier, int rotation_bits)
{
	*chunk *= multiplier;
	*chunk ^= *chunk >> rotation_bits;
	*chunk *= multiplier;
}

/**
 * @brief Finalises the hash value in the MurmurHash algorithm 
 *
 * Performs final mixing operations to improve the hash distribution:
 *   1. XOR with 13-bit right shift
 *   2. Multiply by the magic constant
 *   3. XOR with 15-bit right shift
 *
 * @param hash Pointer to the hash value to finalise
 * @param multiplier The MurmurHash magic constant (0x5bd1e995)
 *
 * @note This avalanche step (雪崩效应是输入微小变化导致输出显著变化的现象。)
 * ensures better distribution of hash values
 * @see hash_function for the complete hashing process
 * @par
 * This is an additional mixing operation to further randomise the hash value,
 * so we can ensure the hash value will be uniformly distributed across the hash
 * table;
 * 
 * The reason why using 13-bit and 15-bit right shifts in this function is based
 * on empirical testing and mathematical principles to achieve the best mixing
 * of bits and enhance the avalanche effect
 *
 * Right shifts are used to mix the higher and lower bits of the hash values
 * Also the creator Austin Appleby found 13-bit and 15-bit shifts provided the
 * best balance of performance and hash quality
 */
static void	finialise_hash(unsigned int *hash, unsigned int multiplier)
{
	*hash ^= *hash >> 13;
	*hash *= multiplier;
	*hash ^= *hash >> 15;
}

/**
 * @brief Generates a hash value for a string key using Murmurhash2
 *
 * Implements a modified version of the Murmurhash2 algorithm:
 *   - Processes the key one byte at a time
 *   - Uses magic constant 0x5bd1e995 for mixing
 *   - Includes string length in initial hash
 *   - Applies avalanceeffect in hash finalisation
 *
 * @param key String to hash
 * @param table_size Size of the hash table (for modular operation)
 * @return size_t Hash value between 0 and ( table_size - 1 )
 *
 * @note in our case, table_size is 128, bash shell is 64
 * @note you can see how the finalise_hash() calculates hash values
 *
 * Properties:
 *   - Deterministic: Same key always produces same hash
 *   - Well-distributed: Minizes clustering
 *   - Fast: O(n) in this hash function time complexity is based on key length
 *
 * @note MurmurHash2 creatd by Austin Appleby
 * @see process_chunk() for chunk processing
 * @see finalise_hash() for hash finialisation
 */
size_t	hash_function(const char *key, size_t table_size)
{
	unsigned int		multiplier;
	unsigned int		hash;
	unsigned int		chunk;
	const unsigned char	*raw_data;

	multiplier = 0x5bd1e995;
	raw_data = (const unsigned char *)key;
	hash = 0 ^ ft_strlen(key);
	while (*key != '\0')
	{
		chunk = *raw_data++;
		process_chunk(&chunk, multiplier, 24);
		hash *= multiplier;
		hash ^= chunk;
		key++;
	}
	finalise_hash(&hash, multiplier);
	return (hash % table_size);
}
/* Not going to use this because of Norm check failure */
// size_t	hash_function(const char *key, size_t table_size)
// {
// 	const unsigned char	*raw_data;
// 	unsigned int		multiplier;
// 	unsigned int		initial_value;
// 	int					rotation_bits;
// 	unsigned int		hash;
// 	unsigned int		chunk;
//
// 	multiplier = 0x5bd1e995; 
// 	initial_value = 0;
// 	rotation_bits = 24;
// 	raw_data = (const unsigned char *)key;
// 	hash = initial_value ^ ft_strlen(key);
// 	while (*key != '\0')
// 	{
// 		chunk = *raw_data++;
// 		chunk *= multiplier;
// 		chunk ^= chunk >> rotation_bits;
// 		chunk *= multiplier;
// 		hash *= multiplier;
// 		hash ^= chunk;
// 		key++;
// 	}
// 	hash ^= hash >> 13;
// 	hash *= multiplier;
// 	hash ^= hash >> 15;
// 	return (hash % table_size);
// }
