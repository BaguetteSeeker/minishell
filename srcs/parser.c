/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/18 00:06:12 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    wipe_ast(t_ast_node *node)
// {
//     if (node == NULL)
//         return ;

//     free_ast(node->left);
//     free_ast(node->right);
//     // free(node->value); // Free the value if it was dynamically allocated
//     free(node);
// }

void	print_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_SUBSHELL)
	{
		ft_printf("Subshell:\n");
		print_ast(node->left);
	}
	else if (node->type == NODE_COMMAND)
	{
		ft_printf("Command: %s\n", node->value);
		//recurse_put(node->args);
		//ft_clean_memtree(node->args);
	}
	else if (node->type == NODE_OPERATOR || node->type == NODE_PIPE)
	{
		ft_printf("Operator: %s\n", node->value);
		ft_printf("Left Node: \n");
		print_ast(node->left);
		ft_printf("Right Node: \n");
		print_ast(node->right);
	}
	node->left = NULL;
	node->right = NULL;
	free(node);
}

//Parses OPAR (untill CPAR found) and/or subsequent WORD tokens
// and returns accodringly a SUBSHELL or COMMANDE node
static t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*node;
	char		**args;
	int			arg_count;

	node = malloc(sizeof(t_ast_node));
	*node = (t_ast_node){0};
	if ((*tokens)->type == OPAR)
	{
		node->type = NODE_SUBSHELL;
		*tokens = (*tokens)->next;
		node->left = parse_tokens(tokens, parse_command(tokens));
		*tokens = (*tokens)->next;
	}
	else
	{
		node->type = NODE_COMMAND;
		node->value = (*tokens)->value;
		*tokens = (*tokens)->next;
		args = malloc(sizeof(char *) * 10);
		if (!args)
			put_err("Parsing : Failled to alloc memory for NODE_COMMAND");
		arg_count = 0;
		while (*tokens && (*tokens)->type == WORD)
		{
			args[arg_count++] = (*tokens)->value;
			*tokens = (*tokens)->next;
		}
		args[arg_count] = NULL;
		node->args = args;
	}
	return (node);
}

//Parses the current token into a node
t_ast_node	*parse_operator(t_token **tokens)
{
	t_ast_node	*operator;

	operator = malloc(sizeof(t_ast_node));
	if (!operator)
		put_err("Parsing : Failled to alloc memory for NODE_OPERATOR");
	*operator = (t_ast_node){0};
	if (((*tokens)->type == AND_IF || (*tokens)->type == OR_IF))
		operator->type = NODE_OPERATOR;
	else if ((*tokens)->type == PIPE)
		operator->type = NODE_PIPE;
	operator->value = (*tokens)->value;
	*tokens = (*tokens)->next;
	return (operator);
}

//Parses one or more subsequent PIPEs into a pipe chain
t_ast_node	*parse_pipe(t_token **tokens)
{
	t_ast_node	*cmd;
	t_ast_node	*operator;

	cmd = parse_command(tokens);
	if ((*tokens)->type != PIPE)
		return (cmd);
	operator = parse_operator(tokens);
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
	node = parse_operator(tokens);
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
		put_err("Uncatched Syntax Error : \
			Expecting Operator token but none was provided");
	return (parse_tokens(tokens, node));
}
