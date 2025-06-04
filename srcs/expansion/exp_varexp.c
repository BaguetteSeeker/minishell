/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_varexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//factorization for norminette
char	*build_concat(t_segment **seg, int *empty, int *from_var, int *q)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (seg[i])
	{
		update_flags(seg[i], empty, from_var, q);
		temp = ft_strjoin(result, seg[i]->text);
		free(result);
		if (!temp)
			return (NULL);
		result = temp;
		i++;
	}
	return (result);
}

//joins all segments into a str
//skips NULL text and in concatenation
//returns NULL char on empty, unquoted expressions
//(NULL str will then be skipped in word_list_to_argv)
char	*concat_segments(t_segment **seg)
{
	char	*result;
	int		empty;
	int		from_var;
	int		unquoted;

	empty = 1;
	from_var = 1;
	unquoted = 1;
	result = build_concat(seg, &empty, &from_var, &unquoted);
	if (!result)
		return (NULL);
	if (empty && from_var && unquoted)
		return (free(result), NULL);
	return (result);
}

//replaces current segment if it's a variable
void	expand_segments(t_segment **seg)
{
	int		i;
	char	*value;

	i = 0;
	while (seg[i])
	{
		if (seg[i]->from_var)
		{
			value = get_value(seg[i]->text);
			if (!value)
			{
				free(seg[i]->text);
				seg[i]->text = ft_strdup("");
			}
			else
			{
				free(seg[i]->text);
				seg[i]->text = ft_strdup(value);
			}
		}
		i++;
	}
}

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


//Main function of actual variable expansion
//for each word on the list, creates an array of sub-segments describing
//sections of the word that may need to be expanded
//each segment's expansion behavior is defined by its quoting context
//after expansion, each segments in array are concatenated into a new word
//said new word is marked for splitting or not in next stage of global exp
void	var_exp(t_word *list)
{
	t_segment	**seg;
	char		*new;

	while (list)
	{
		seg = parse_segments(list->text);
		if (!seg)
			return ;
		// printf("\nbedore exp :");
		// print_segments(seg);
		expand_segments(seg);
		// printf("after exp :");
		// print_segments(seg);
		new = concat_segments(seg);
		if (!new)
		{
			free(list->text);
			list->text = NULL;
		}
		else
		{
			free(list->text);
			list->text = new;
		}
		list->should_split = should_word_split(seg);
		free_segments(seg);
		list = list->next;
	}
}
