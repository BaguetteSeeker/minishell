/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/12 23:18:42 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parses one or more subsequent PIPEs into a pipe chain
static t_ast_node	*parse_pipe(t_token **tokens)
{
	t_ast_node	*cmd;
	t_ast_node	*operator;

	cmd = parse_command(tokens);
	if ((*tokens)->type != PIPE)
		return (cmd);
	operator = init_node(tokens);
	operator->left = cmd;
	operator->right = parse_pipe(tokens);
	return (operator);
}

t_ast_node	*parse_tokens(t_token **tokens, t_ast_node *passed_node)
{
	t_ast_node	*node;
	t_ast_node	*prev_cmd;

	if (!passed_node)
		return (parse_tokens(tokens, parse_command(tokens)));
	else
		prev_cmd = passed_node;
	if (!(*tokens) || (*tokens)->type == T_NEWLINE || (*tokens)->type == CPAR)
		return (passed_node);
	node = init_node(tokens);
	node->left = prev_cmd;
	if (node->type == NODE_PIPE)
		node->right = parse_pipe(tokens);
	else if (node->type == NODE_OPERATOR)
	{
		node->right = parse_command(tokens);
		if ((*tokens)->type == PIPE)
			node->right = parse_tokens(tokens, node->right);
	}
	else
		put_err(ERRMSG_MISSING_OPTOK);
	return (parse_tokens(tokens, node));
}
