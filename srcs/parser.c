/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/15 10:28:36 by epinaud          ###   ########.fr       */
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
        recurse_put(node->args);
        //ft_clean_memtree(node->args);
        // print_ast(node->left);
        // print_ast(node->right);
    }
    else if (node->type == NODE_OPERATOR)
    {
        ft_printf("Operator: %s\n", node->value);
        print_ast(node->left);
        print_ast(node->right);
    }
    node->left = NULL;
    node->right = NULL;
    free(node);
}


//Won't work as pointer shift must be done before the subtree are parsed
void    assert_precedence(t_ast_node **top_node, t_ast_node **sub_node)
{
	t_ast_node	*tmp;

    if (ft_strcmp((*top_node)->value, "||")
		&& (ft_strcmp((*sub_node)->value, "&&") || ft_strcmp((*sub_node)->value, "|")))
	{
		tmp = *top_node;
		ft_printf("Swapping ptr %p || for %p &&\n", *top_node, *sub_node);
		ft_swap((long *)top_node, (long *)sub_node);
		ft_swap((long *)&((*top_node)->right), (long *)&tmp);
	}
}

t_ast_node *parse_tokens(t_token **tokens)
{
	t_ast_node *node;
	t_ast_node *logic_node;

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

		char **args = malloc(sizeof(char *) * 10); // Example: max 10 arguments
		int arg_count = 0;

		// Collect arguments (subsequent WORD tokens)
		while (*tokens && (*tokens)->type == WORD)
		{
			args[arg_count++] = (*tokens)->value; // Store argument
			*tokens = (*tokens)->next; // Move to the next token
		}
		args[arg_count] = NULL; // Null-terminate the arguments array
		node->args = args; // Assign arguments to the node
	}
   
	if (*tokens && ((*tokens)->type == AND_IF || (*tokens)->type == OR_IF))
	{
		logic_node = malloc(sizeof(t_ast_node));
		*logic_node = (t_ast_node){0};
		logic_node->type = NODE_OPERATOR;
		logic_node->value = (*tokens)->value; // Store the operator (e.g., "&&" or "||")
		*tokens = (*tokens)->next; // Move to the next token

		logic_node->left = node; // Attach the current node as the left child
		logic_node->right = parse_tokens(tokens); // Parse the right operand
		ft_printf("Before assert : Top node is %p and sub node is %p \n", logic_node, logic_node->right);
		assert_precedence(&logic_node, &logic_node->right);
		ft_printf("After assert : Top node is %p and sub node is %p \n--\n", logic_node, logic_node->right);
		node = logic_node; // Update the current node to the operator node
	}
	return (node);
}