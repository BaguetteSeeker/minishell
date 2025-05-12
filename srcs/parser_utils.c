/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:35 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/12 17:35:52 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Parses the current token into a node
t_ast_node	*init_node(t_token **tokens)
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
	else
	{
		node->type = NODE_COMMAND;
		return (node);
	}
	node->value = (*tokens)->value;
	*tokens = (*tokens)->next;
	return (node);
}

static char	**parse_args(t_token **tokens, size_t parse_type)
{
	char	**args;
	int		arg_count;

	args = NULL;
	arg_count = 0;
	while (*tokens && (*tokens)->type == WORD && (
			(parse_type == PARSE_SUBSQ_WORDS)
			|| (parse_type == PARSE_SUBSQ_VARS
				&& ft_strchr((*tokens)->value, '='))))
	{
		args = ft_realloc(args, sizeof(char *) * (arg_count + 2));
		if (!args)
			put_err("Parsing : Failled to alloc memory for NODE_COMMAND");
		args[arg_count++] = (*tokens)->value;
		*tokens = (*tokens)->next;
	}
	args[arg_count] = NULL;
	return (args);
}

static t_redir	*parse_redir(t_token **tokens)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		put_err("Parser Utils : Malloc faillure");
	*redir = (t_redir){(*tokens)->next->value, NULL, (*tokens)->type};
	*tokens = (*tokens)->next->next;
	return (redir);
}

static char	*parse_pathname(t_token **tokens)
{
	char	*pathname;

	pathname = (*tokens)->value;
	*tokens = (*tokens)->next;
	return (pathname);
}

#define REDIRS_TYPCOUNT 4
//Parses OPAR (untill CPAR found)
//Then parses and/or subsequent WORD tokens
// and returns accodringly a SUBSHELL or COMMANDE node
t_ast_node	*parse_command(t_token **tokens)
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
		if (!node->value && (*tokens)->type == WORD
			&& ft_strchr((*tokens)->value, '='))
			node->vars = parse_args(tokens, PARSE_SUBSQ_VARS);
		if (!node->value && (*tokens)->type == WORD)
			node->value = parse_pathname(tokens);
		if (in_array((*tokens)->type, cmd_parts, REDIRS_TYPCOUNT)
			&& (*tokens)->next->type == WORD)
			lstadd_back_redirs(&node->io_streams, parse_redir(tokens));
		else if ((*tokens)->type == WORD)
			node->args = parse_args(tokens, PARSE_SUBSQ_WORDS);
		else
			return (node);
	}
}
