/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putlogs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:24:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 12:36:41 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_list(t_redir *redir)
{
	int	i = 0;
	while (redir)
	{
		printf("redir #%d -> file: [%s], type: %d\n", i, redir->file, redir->type);
		redir = redir->next;
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		printf("Tab NULL\n");
	while (tab && tab[i])
	{
		printf("%d\t>%s<\n",i, tab[i]);
		i++;
	}
}

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("Node does not exist", 1));
	ft_putstr_fd("Content > : ", 1);
	ft_putstr_fd(lst->value, 1);
	ft_printf(" of type [%d]\n", lst->type);
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
