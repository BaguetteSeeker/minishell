/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/21 00:15:30 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parses the current token into a node
static t_ast_node	*init_node(t_token **tokens)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		put_err("Parsing : Failled to alloc memory for new NODE");
	*node = (t_ast_node){0};
	if (((*tokens)->type == AND_IF || (*tokens)->type == OR_IF))
		node->type = NODE_OPERATOR;
	else if ((*tokens)->type == PIPE)
		node->type = NODE_PIPE;
	else if ((*tokens)->type == OPAR)
		node->type = NODE_SUBSHELL;
	else if ((*tokens)->type == WORD)
		node->type = NODE_COMMAND;
	else
		return (node);
	node->value = (*tokens)->value;
	*tokens = (*tokens)->next;
	return (node);
}

static char	**parse_args(t_token **tokens)
{
	char	**args;
	int		arg_count;

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
	return (args);
}

static t_redir	*parse_redir(t_token **tokens)
{
	t_redir	*redir;

	// redir = (t_redir *)ft_lstnew((t_token *)(&(t_redir){0}));
	redir = malloc(sizeof(t_redir));
	if (!redir)
		put_err("Failled allocation for redirection");
	*redir = (t_redir){(*tokens)->type, (*tokens)->next->value, NULL};
	*tokens = (*tokens)->next->next;
	// ft_lstadd_back((t_token **)redirs, (t_token *)redir);
	ft_printf("Pointer for redir %p and content %s\n", redir, redir->file);
	return (redir);
}

#define REDIRS_TYPCOUNT 4

//Parses OPAR (untill CPAR found)
//Then parses and/or subsequent WORD tokens
// and returns accodringly a SUBSHELL or COMMANDE node
static t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*node;
	static int	cmd_parts[] = {LESS, GREAT, DLESS, DGREAT};

	node = init_node(tokens);
	if (node->type == NODE_SUBSHELL)
	{
		node->left = parse_tokens(tokens, parse_command(tokens));
		*tokens = (*tokens)->next;
	}
	while (1)
	{
		if (!node->value && (*tokens)->type == WORD)
		{
			node->value = (*tokens)->value;
			*tokens = (*tokens)->next;
		}
		if (in_array((*tokens)->type, cmd_parts, REDIRS_TYPCOUNT)
			&& (*tokens)->next->type == WORD)
			lstadd_back_redirs(node->io_streams, parse_redir(tokens));
		else if ((*tokens)->type == WORD)
			node->args = parse_args(tokens);
		else
			return (node);
	}
}

//Parses one or more subsequent PIPEs into a pipe chain
t_ast_node	*parse_pipe(t_token **tokens)
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
		put_err("Uncatched Syntax Error : \
			Expecting Operator token but none was provided");
	return (parse_tokens(tokens, node));
}
