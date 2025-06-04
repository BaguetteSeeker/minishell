/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_linkedlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cool pointer logic
//takes the node following the insertion point as argument
//iteratively creates new nodes and swap the "after" with created node
//effectively taking its place, previous node->next points to the new nodes
t_word	*insert_split_words(char **split, t_word *after)
{
	t_word	*prev;
	t_word	*new;

	prev = after;
	while (*split)
	{
		new = create_new_word(*split);
		if (!new)
			return (NULL);
		new->previous = prev;
		new->next = prev->next;
		if (prev->next)
			prev->next->previous = new;
		prev->next = new;
		prev = new;
		split++;
	}
	update_node_index(prev);
	return (prev);
}

t_word	*create_new_word(char *text)
{
	t_word	*node;

	node = malloc(sizeof(t_word));
	if (!node)
		return (NULL);
	node->text = ft_strdup(text);
	if (!node->text)
		return (free(node), NULL);
	node->should_split = 1;
	node->from_variable = 0;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

//creates a list from argv
t_word	*word_list_from_argv(char **argv)
{
	t_word	*head;
	t_word	*current;
	t_word	*new;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	while (argv[i])
	{
		new = create_new_word(argv[i]);
		if (!new)
			return (NULL);
		new->index = i;
		if (!head)
			head = new;
		else
		{
			current->next = new;
			new->previous = current;
		}
		current = new;
		i++;
	}
	return (head);
}

//again, factorization for norm compliance
static char	**fill_argv_array(char **argv, t_word *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->text)
		{
			argv[i] = strdup(list->text); //leak
			if (!argv[i])
			{
				while (i > 0)
					free(argv[--i]);
				free(argv);
				return (NULL);
			}
			i++;
		}
		list = list->next;
	}
	argv[i] = NULL;
	return (argv);
}

//recreate argv from list, skipping NULL char *text (unset VAR and empty word)
char	**word_list_to_argv(t_word *list)
{
	char	**argv;
	int		count;
	t_word	*tmp;

	tmp = list;
	count = count_non_null_words(list);
	argv = malloc(sizeof(char *) * (count + 1)); //DEFF lost (wtf)
	if (!argv)
		return (free_word_list(list), NULL);
	argv = fill_argv_array(argv, list);
	if (!argv)
		return (NULL);
	free_word_list(tmp);
	return (argv);
}
