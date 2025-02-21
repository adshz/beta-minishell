/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:16 by szhong            #+#    #+#             */
/*   Updated: 2025/02/19 18:45:36 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef AST_H
# define AST_H
# include "parser_types.h"

void		free_ast(t_ast_node *ast);
t_ast_node	*create_ast_node(t_ast_type type, char *value);
bool		is_valid_ast(void *ast);
t_token		*find_last_word_token(t_token *start);

#endif 
