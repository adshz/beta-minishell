/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tracker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:58:21 by szhong            #+#    #+#             */
/*   Updated: 2025/03/04 15:58:23 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include "memory_collector/memory_collector.h"

char	*tracked_strdup(const char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	return (ft_hash_memory_collector(str, false));
}

char	*tracked_itoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		return (NULL);
	return (ft_hash_memory_collector(str, false));
}

t_list	*tracked_lstnew(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		return (NULL);
	return (ft_hash_memory_collector(node, false));
}
