/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:35 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/06 11:24:07 by epinaud          ###   ########.fr       */
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

//Work off of the node' args 
static char	**parse_args(t_token **tokens, char ***list, size_t parse_type)
{
	int		arg_count;

	if (*list == NULL)
		arg_count = 0;
	else
		arg_count = ft_ptrlen((const void **)*list);
	while (*tokens && (*tokens)->type == WORD && (
			(parse_type == PARSE_SUBSQ_WORDS)
			|| (parse_type == PARSE_SUBSQ_VARS
				&& ft_strchr((*tokens)->value, '=')
				&& check_varname((*tokens)->value))))
	{
		*list = ft_realloc(*list, sizeof(char *) * (arg_count + 2),
				sizeof(char *) * (arg_count));
		if (!*list)
			put_err("Parsing : Malloc Faillure");
		(*list)[arg_count] = ft_strdup((*tokens)->value);
		if (!(*list)[arg_count])
			put_err("Parsing : Malloc Faillure");
		(*list)[++arg_count] = NULL;
		*tokens = (*tokens)->next;
	}
	return (*list);
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

#define REDIRS_TYPCOUNT 4
//Handles parsing of Subshells and Commands' : args, redirs and vars
t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*node;
	static int	redirs[] = {LESS, GREAT, DLESS, DGREAT};

	node = init_node(tokens);
	if (node->type == NODE_SUBSHELL)
	{
		node->left = parse_tokens(tokens, parse_command(tokens));
		*tokens = (*tokens)->next;
	}
	while (1)
	{
		if (!node->args && (*tokens)->type == WORD
			&& ft_strchr((*tokens)->value, '='))
			node->vars = parse_args(tokens, &node->vars, PARSE_SUBSQ_VARS);
		if (in_array((*tokens)->type, redirs, REDIRS_TYPCOUNT)
			&& (*tokens)->next->type == WORD)
			msh_lstaddback(&node->io_streams, parse_redir(tokens));
		else if ((*tokens)->type == WORD)
			node->args = parse_args(tokens, &node->args, PARSE_SUBSQ_WORDS);
		else
			return (node);
	}
}
