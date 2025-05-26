/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:05:17 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/18 18:20:00 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//for each node, print it with the corresponding color
void	draw_ast_node_label(t_ast_node *node, const char *prefix, const char *c)
{
	if (node->type == NODE_COMMAND)
		ft_printf("%s%s%s%s%s\n",
			prefix, c, COLOR_WHITE_BOLD, node->value, COLOR_RESET);
	else if (node->type == NODE_OPERATOR)
		ft_printf("%s%s%s\b(%s)%s\n",
			prefix, c, COLOR_RED, node->value, COLOR_RESET);
	else if (node->type == NODE_PIPE)
		ft_printf("%s%s%s\b(|)%s\n",
			prefix, c, COLOR_RED, COLOR_RESET);
	else if (node->type == NODE_SUBSHELL)
		ft_printf("%s%s%s\b(subshell)%s\n",
			prefix, c, COLOR_RED, COLOR_RESET);
}

void	draw_ast_node_var(t_ast_node *node, const char *prefix, int is_left)
{
	int	i;

	i = 0;
	if (node->type == NODE_COMMAND && node->vars)
	{
		if (is_left)
			ft_printf("%s    var:", prefix);
		else
			ft_printf("%s│   var:", prefix);
		while (node->vars[i])
		{
			ft_printf("(%d) %s    ", i + 1, node->vars[i]);
			i++;
		}
		ft_printf("\n");
	}
}

void	draw_ast_node_args(t_ast_node *node, const char *prefix, int is_left)
{
	int	i;

	i = 0;
	if (node->type == NODE_COMMAND && node->args)
	{
		if (is_left)
			ft_printf("%s    args:", prefix);
		else
			ft_printf("%s│   args:", prefix);
		while (node->args[i])
		{
			ft_printf("(%d) %s    ", i + 1, node->args[i]);
			i++;
		}
		ft_printf("\n");
	}
}

void	draw_ast_node_redirs(t_ast_node *node, const char *prefix, int is_left)
{
	t_redir	*redir;

	if (node->type == NODE_COMMAND && node->io_streams)
	{
		if (is_left)
			ft_printf("%s    redirs:", prefix);
		else
			ft_printf("%s│   redirs:", prefix);
		redir = node->io_streams;
		while (redir)
		{
			if (redir->type == REDIR_IN)
				ft_printf(" < %s\n", redir->file);
			else if (redir->type == REDIR_OUT)
				ft_printf(" > %s\n", redir->file);
			else if (redir->type == APPEND)
				ft_printf(" >> %s\n", redir->file);
			else if (redir->type == HEREDOC)
				ft_printf(" << %s\n", redir->file);
			else
				ft_printf(" ? %s\n", redir->file);
			redir = redir->next;
		}
	}
}

//draws each node recursively, using DFS search 
//draws righmost nodes first (higher on terminal)
//prefix denotes the depth of the print
void	draw_ast(t_ast_node *node, const char *prefix, int is_left)
{
	char	*next_prefix;
	char	*connector;

	if (!node)
		return ;
	if (is_left)
		next_prefix = ft_strjoin(prefix, "│   ");
	else
		next_prefix = ft_strjoin(prefix, "    ");
	draw_ast(node->right, next_prefix, 0);
	free(next_prefix);
	if (is_left)
		connector = "└── ";
	else
		connector = "┌── ";
	draw_ast_node_label(node, prefix, connector);
	draw_ast_node_args(node, prefix, is_left);
	draw_ast_node_var(node, prefix, is_left);
	draw_ast_node_redirs(node, prefix, is_left);
	if (is_left)
		next_prefix = ft_strjoin(prefix, "    ");
	else
		next_prefix = ft_strjoin(prefix, "│   ");
	draw_ast(node->left, next_prefix, 1);
	free(next_prefix);
}
