/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}

void	free_exp(t_ast_node *node)
{
	t_redir	*redir;

	redir = node->io_streams;
	if (node->exp_args)
		free_tab((void **)node->exp_args);

	while (redir)
	{
		if (redir->exp_file)
		{
			free(redir->exp_file);
			redir->exp_file = NULL;
		}
		redir = redir->next;
	}
}
