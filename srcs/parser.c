/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/12 19:18:28 by epinaud          ###   ########.fr       */
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

// void    wipe_ast(t_ast_node *node)
// {
//     if (node == NULL)
//         return ;

//     free_ast(node->left);
//     free_ast(node->right);
//     // free(node->value); // Free the value if it was dynamically allocated
//     free(node);
// }

void    print_ast(t_ast_node *node)
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
        print_ast(node->left);
        print_ast(node->right);
    }
    else if (node->type == NODE_OPERATOR)
    {
        ft_printf("Operator: %s\n", node->value);
        print_ast(node->left);
        print_ast(node->right);
    }
}

t_ast_node *parse_tokens(t_token **tokens)
{
    t_ast_node *node = NULL;

    if (!*tokens)
        return NULL;
    node = malloc(sizeof(t_ast_node));
    *node = (t_ast_node){0};
    if ((*tokens)->type == OPAR) // Handle subshell
    {
        *tokens = (*tokens)->next; // Skip '(
        node->type = NODE_SUBSHELL;
        node->left = parse_tokens(tokens);
        *tokens = (*tokens)->next; // Skip ')'
    }
    else if ((*tokens)->type == WORD) // Handle command
	{
        node->type = NODE_COMMAND;
        node->value = (*tokens)->value;
        *tokens = (*tokens)->next;
        node->left = parse_tokens(tokens); // Parse the left operand
        node->right = parse_tokens(tokens); // Parse the right operand
        //allocate char **for params
		// while ((*tokens)->type == WORD)
		// {
		// 	// node->value = ft_strdup((*tokens)->value);
		// 	*tokens = (*tokens)->next; // Move to the next token
		// }
        // char **args = malloc(sizeof(char *) * 10); // Example: max 10 arguments
        // int arg_count = 0;

        // // Collect arguments (subsequent WORD tokens)
        // while (*tokens && (*tokens)->type == WORD)
        // {
        //     args[arg_count++] = ft_strdup((*tokens)->value); // Store argument
        //     *tokens = (*tokens)->next; // Move to the next token
        // }
        // args[arg_count] = NULL; // Null-terminate the arguments array
        // node->args = args; // Assign arguments to the node
    }
    else if ((*tokens)->type == AND_IF || (*tokens)->type == OR_IF)
    {
        node->type = NODE_OPERATOR;
        node->value = (*tokens)->value;
        *tokens = (*tokens)->next; // Move to the next token
        node->left = parse_tokens(tokens); // Parse the left operand
        node->right = parse_tokens(tokens); // Parse the right operand
    }
    return (node);
}