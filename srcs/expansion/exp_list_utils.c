/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_word_list(t_word *list)
{
	t_word	*tmp;

	while (list->previous != NULL)
		list = list->previous;
	while (list)
	{
		tmp = list->next;
		if (list->text)
			free(list->text);
		if (list->seg)
			free_segments(list->seg);
		free(list);
		list = tmp;
	}
}

//updates the index
int	update_node_index(t_word *lst)
{
	int	i;

	i = 0;
	while (lst->previous != NULL)
		lst = lst->previous;
	while (lst)
	{
		lst->index = i;
		i++;
		lst = lst->next;
	}
	return (i);
}

void	remove_word(t_word *node)
{
	if (!node)
		return ;
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	if (node->next)
		update_node_index(node->next);
	else if (node->previous)
		update_node_index(node->previous);
	if (node->text)
	{
		free(node->text);
		node->text = NULL;
	}
	if (node->seg)
	{
		free_segments(node->seg);
		node->seg = NULL;
	}
	free(node);
}

int	count_non_null_words(t_word *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->text)
			count++;
		list = list->next;
	}
	return (count);
}
