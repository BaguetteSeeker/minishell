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

//word is only splitable if there's at least on segment unquoted AND 
//contains a space (tough one)
//example :
//VAR1="oui non"
//VAR2="123"
//$VAR1$VAR2 expands to : oui non123 (should split to "oui" and "non123")
//VAR3="oui non"
//$VAR3 expands to : oui non SHOULD split
//"$VAR3" expands to : "oui non", shouldn't split
//OUI"non oui" expands to : OUInon oui, one word, shouldn't split either
int	should_word_split(t_segment **seg)
{
	int	i;

	if (!seg)
		return (0);
	i = 0;
	while (seg[i])
	{
		if (seg[i]->quote == QUOTE_NONE
			&& contains_unquoted_space(seg[i]))
			return (1);
		i++;
	}
	return (0);
}


//use ft_split, replace current node with first end of split
//insert a new node with second end of split
int	split_and_replace(t_word *cur)
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

//for each word evaluate if word is splittable
//if so, split it in place
void	word_split(t_word **head)
{
	t_word	*cur;
	t_word	*next;

	if (!head || !*head)
		return;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		cur->should_split = should_word_split(cur->seg);
		if (cur->should_split && cur->text)
		{
			if (split_and_replace(cur))
				return ;
			if (!cur->text)
				*head = next;
		}
		cur = next;
	}
	update_node_index(*head);
}

//on each word, if wildcard is expandable
//	-get char ** array of matching files
//	-inset array into new nodes in word list
//	-remove current expanded wildcard word
void	exp_wildcards(t_word **head)
{
	t_word	*current;
	char	**expanded;
	t_word	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		if (current->seg && current->text && ft_strchr(current->text, '*')
			&& is_wildcard_expandable(current->seg))
		{
			expanded = get_path(current->text);
			if (!expanded)
				return ;
			insert_split_words(expanded, current);
			if (current == *head)
				*head = current->next;
			remove_word(current);
			free_tab((void **)expanded);
		}
		current = next;
	}
}

//main expansion function
//	-turn args into list of words
//	-for each word, expands text using segmentation logic
//	-if marked for splitting, split it into multiple argv
//	-similar although simpler process for node->var (no word_splitting)
//	=====	WIP	=====
//	-expands redirections
//	-wildcard globbing
//https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html 2.6
int	expand_node(t_ast_node *node)
{
	t_word	*word_lst;
	int		ret;

	ret = 0;
	if (node->io_streams)
		ret = expand_redirs(node);
	if (ret)
		return (1);
	if (node->vars)
		expand_vars(node);
	if (node->args)
	{
		word_lst = word_list_from_argv(node->args);
		if (!word_lst)
			return (1);
		// print_word_list(word_lst);

		var_exp(word_lst);
		// printf("after var exp :\n");	
		// print_word_list(word_lst);
		word_split(&word_lst);
		// printf("after split exp :\n");	
		// print_word_list(word_lst);
		exp_wildcards(&word_lst);
		// printf("after wldcrd exp :\n");	
		// print_word_list(word_lst);
		// printf("\n=== EXP end ===\n");
		node->exp_args = word_list_to_argv(word_lst);
		// print_tab(node->exp_args);
		
	}
	// printf("\nexp args :\n");
	// print_tab(node->exp_args);
	// printf("\nexp vars :\n");
	// print_tab(node->exp_vars);
	// printf("\n\n%p is NULL ???\n\n", node->io_streams);
	// if (node->io_streams)
		// printf("old file %s, new %s\n", node->io_streams->file, node->io_streams->exp_file);
	return (0);
}
