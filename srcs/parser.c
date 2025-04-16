/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/16 12:35:56 by epinaud          ###   ########.fr       */
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

static t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node *node;
	
	// if (!*tokens)
	// 	return NULL;
	node = malloc(sizeof(t_ast_node));
	*node = (t_ast_node){0};

	if ((*tokens)->type == OPAR) // Handle subshell
	{
		*tokens = (*tokens)->next; // Skip '(
		node->type = NODE_SUBSHELL;
		node->left = parse_tokens(tokens, parse_command(tokens));
		*tokens = (*tokens)->next; // Skip ')'
	}
	else 
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

	return (node);
}

//!token retun passed node
//!passed_node parse the leftmost cmd
//call parse_token with said node as param
//if passed node ! null attach it to right of node_operator
//then pass node_operator to parse_tokens
//return parse_token result
t_ast_node *parse_tokens(t_token **tokens, t_ast_node *passed_node)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	*node = (t_ast_node){0};  
	if (!(*tokens) || (*tokens)->type == T_NEWLINE || (*tokens)->type == CPAR)
		return (passed_node);
	if (!passed_node)
		node = parse_command(tokens);
	else if (((*tokens)->type == AND_IF || (*tokens)->type == OR_IF))
	{
		node->type = NODE_OPERATOR;
        node->value = (*tokens)->value; // Store the operator (e.g., "&&" or "||")
        *tokens = (*tokens)->next; // Move to the next token
		node->left = passed_node;
		node->right = parse_tokens(tokens, parse_command(tokens));
	}
	else if ((*tokens)->type == PIPE)
	{
		node->type = NODE_PIPE;
        node->value = (*tokens)->value; // Store the operator (e.g., "&&" or "||")
		*tokens = (*tokens)->next; // Move to the next token
		passed_node->right = node;
	}
	else if ((*tokens)->type == WORD)
		return (parse_command(tokens));
	else
		put_err("Uncatched Syntax Error : Expecting Operator token but none was provided");
	return (node);
}