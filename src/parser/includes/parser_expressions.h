/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expressions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:41:49 by szhong            #+#    #+#             */
/*   Updated: 2025/02/19 18:41:54 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_EXPRESSIONS_H
# define PARSER_EXPRESSIONS_H

t_ast_node	*parse_expression(t_token **tokens, t_shell *shell);
t_ast_node	*build_expression_tree(t_token **tokens, t_shell *shell);

#endif
