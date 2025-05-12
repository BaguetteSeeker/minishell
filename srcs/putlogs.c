/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putlogs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:24:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/12 12:38:06 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("Node does not exist", 1));
	ft_putstr_fd("Node content > : ", 1);
	ft_putstr_fd(lst->value, 1);
	ft_printf(" of type %d\n", lst->type);
}

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
		ft_putendl_fd("Printing vars :", 1);
		put_recurse_dynarr(node->vars);
		ft_putendl_fd("Printing args :", 1);
		put_recurse_dynarr(node->args);
		ft_putendl_fd("Printing redirs:", 1);
		msh_lstiter((node->io_streams), lst_put);
	}
	else if (node->type == NODE_OPERATOR || node->type == NODE_PIPE)
	{
		ft_printf("Operator: %s\n", node->value);
		ft_printf("Left Node: \n");
		print_ast(node->left);
		ft_printf("Right Node: \n");
		print_ast(node->right);
	}
}
