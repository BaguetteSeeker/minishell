/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_segment_utis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//from var interface, on single char instead of whole str
int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

//return 1 on variable start
//variable start defined as allowed variable char positionned after $ 
int	is_var_start(const char *s, t_quote q)
{
	if (!s || *s != '$')
		return (0);
	if (q == QUOTE_SINGLE)
		return (0);
	if (*(s + 1) == '?')
		return (1);
	if (!is_var_char(*(s + 1)))
		return (0);
	return (1);
}

//updates quote condition of segment
int	update_quote(char c, t_quote *q)
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

//increments i to skip outer quotes using quote condition
void	skip_standalone_quotes(const char *str, int *i, t_quote *q)
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
