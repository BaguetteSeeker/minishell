/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/11 10:21:38 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *tokens)
{
	while (tokens)
	{
		//if logic
			//Allocate logic node
			//
		//Allocate cmd_node
		//Add cmd_name
		//Add cmd_args
		tokens = tokens->next;
	}
	return (0);
}

t_ast_node *parse_tokens(t_token **tokens)
{
    t_ast_node *node = NULL;

    if (!*tokens)
        return NULL;
    node = malloc(sizeof(t_ast_node));
    if ((*tokens)->type == OPAR) // Handle subshell
    {
        *tokens = (*tokens)->next; // Skip '(
        node->type = NODE_SUBSHELL;
        node->left = parse_tokens(tokens); // Parse the content of the subshell
        if ((*tokens)->type != CPAR)
        {
            ft_dprintf(STDERR_FILENO, "Syntax error: unmatched parentheses\n");
            free(node);
            return NULL;
        } 
        *tokens = (*tokens)->next; // Skip ')'
    }
    else if ((*tokens)->type == WORD) // Handle command
	{
        //Detokenize the command
        //allocate char **for params
        node->type = NODE_COMMAND;
		while ((*tokens)->type == WORD)
		{
			node->type = NODE_COMMAND;
			node->value = ft_strdup((*tokens)->value);
			*tokens = (*tokens)->next; // Move to the next token
		}
    }
    else if ((*tokens)->type == AND_IF || (*tokens)->type == OR_IF) // Handle operator
    {
        node->type = NODE_OPERATOR;
        node->value = ft_strdup((*tokens)->value);
        *tokens = (*tokens)->next; // Move to the next token
        node->left = parse_tokens(tokens); // Parse the left operand
        node->right = parse_tokens(tokens); // Parse the right operand
    }
    return (node);
}