/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parse_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote(char c, quote_t *q)
{
	if (c == '\'' && *q == QUOTE_NONE)
		return (*q = QUOTE_SINGLE, 1);
	if (c == '\'' && *q == QUOTE_SINGLE)
		return (*q = QUOTE_NONE, 1);
	if (c == '"' && *q == QUOTE_NONE)
		return (*q = QUOTE_DOUBLE, 1);
	if (c == '"' && *q == QUOTE_DOUBLE)
		return (*q = QUOTE_NONE, 1);
	return (0);
}

t_segment	*create_new_segment(char *text, quote_t quote, int from_var)
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

void	skip_standalone_quotes(const char *str, int *i, quote_t *q)
{
	if ((str[*i] == '"' && *q != QUOTE_SINGLE)
		|| (str[*i] == '\'' && *q != QUOTE_DOUBLE))
	{
		update_quote(str[*i], q);
		(*i)++;
	}
}

int	var_len(const char *s)
{
	int	i;

	i = 0;
	if (!is_var_char(s[i]))
		return (0);
	while (is_var_char(s[i]))
		i++;
	return (i);
}

//from var interface, on single char instead of str
int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}