/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_memory_tracker.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:00 by your_username     #+#    #+#             */
/*   Updated: 2024/03/19 10:00:00 by your_username    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_MEMORY_TRACKER_H
# define AST_MEMORY_TRACKER_H

# include "parser/parser.h"

t_list		**get_ast_mem_list(void);
t_ast_node	*track_ast_node(t_ast_node *node);
void		cleanup_ast_nodes(void);

#endif 
