/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/09 22:48:38 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_node_type {
    NODE_COMMAND,
    NODE_OPERATOR,
    NODE_SUBSHELL,
    NODE_REDIRECTION
} t_node_type;

typedef struct s_ast_node {
    t_node_type type;          // Type of the node (command, operator, subshell, etc.)
    char *value;               // Value of the node (e.g., command name, operator)
    struct s_ast_node *left;   // Left child (e.g., left operand of an operator)
    struct s_ast_node *right;  // Right child (e.g., right operand of an operator)
    struct s_ast_node *subtree; // Subtree for subshells or compound commands
} t_ast_node;

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
        node->subtree = parse_tokens(tokens); // Parse the content of the subshell
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