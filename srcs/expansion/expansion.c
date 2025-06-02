/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_and_replace(t_word *cur)
{
	char	**split;
	t_word	*new_tail;

	split = ft_split(cur->text, ' ');
	free(cur->text);
	if (!split)
		return (1);
	if (split[0])
		cur->text = ft_strdup(split[0]);
	else
		cur->text = NULL;
	if (!cur->text && split[0])
	{
		free_tab((void **)split);
		return (1);
	}
	new_tail = insert_split_words(&split[1], cur);
	free_tab((void **)split);
	if (new_tail)
		cur = new_tail;
	return (0);
}

void	word_split(t_word *head)
{
	t_word	*cur;

	cur = head;
	while (cur)
	{
		if (cur->should_split && cur->text)
		{
			if (split_and_replace(cur))
				return ;
		}
		cur = cur->next;
	}
	update_node_index(head);
}

//main expansion function
//	-turn args into list of words
//	-for each word, expands text using segmentation logic
//	-if marked for splitting, split it into multiple argv

//	-similar process for node->vars
//	-expands redirections
//	-(wildcard globbing ?)
int	expand_node(t_ast_node *node)
{
	t_word	*word_lst;

	word_lst = word_list_from_argv(node->args);
	if (!word_lst)
		return (1);
	print_word_list(word_lst);

	var_exp(word_lst);

	printf("after var exp :\n");	
	print_word_list(word_lst);
	word_split(word_lst);

	print_word_list(word_lst);
	printf("\n=== EXP end ===\n");
	node->new_args = word_list_to_argv(word_lst);
	print_tab(node->new_args);
	return (0);
}
