/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_varexp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*create_new_segment(char *text, t_quote quote, int from_var)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->text = text;
	seg->quote = quote;
	seg->from_var = from_var;
	return (seg);
}

void	free_segments(t_segment	**seg)
{
	int	i;

	i = 0;
	while (seg && seg[i])
	{
		if (seg[i]->text)
			free(seg[i]->text);
		free(seg[i]);
		i++;
	}
	free(seg);
	return ;
}

//updates values of local function flags (in stack) to match segments flag
void	update_flags(t_segment *s, int *empty, int *from_var, int *q)
{
	if (s->text && s->text[0] != '\0')
		*empty = 0;
	if (!s->from_var)
		*from_var = 0;
	if (s->quote != QUOTE_NONE)
		*q = 0;
}

//helper for expand_segments
char	*get_value(char *s)
{
	char	*value;

	value = get_var_value(VAR_ENV, s);
	if (!value)
		value = get_var_value(VAR_SHELL, s);
	return (value);
}

//helper for split evaluation
int	contains_unquoted_space(t_segment *s)
{
	int	i;

	i = 0;
	while (s->text && s->text[i])
	{
		if (s->text[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}