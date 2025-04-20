/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:24:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/20 22:46:03 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		recurse_put(node->args);
		ft_lstiter(((t_token *)node->io_streams), lst_put);
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

// void    wipe_ast(t_ast_node *node)
// {
//     if (node == NULL)
//         return ;

//     free_ast(node->left);
//     free_ast(node->right);
//     // free(node->value); // Free the value if it was dynamically allocated
//     free(node);
// }
