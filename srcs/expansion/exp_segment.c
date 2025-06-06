/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return 1 on variable start
//variable start defined as allowed variable char positionned after $ 
int	is_var_start(const char *s, quote_t q)
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

//from start of var to change in quote OR unallowed char
int	scan_segment_len(const char *s, int start, quote_t *q)
{
	int	len;

	len = 0;
	while (s[start + len])
	{
		if (is_var_start(&s[start + len], *q))
			break ;
		if ((s[start + len] == '\'' && *q != QUOTE_DOUBLE)
			|| (s[start + len] == '"' && *q != QUOTE_SINGLE))
			break ;
		len++;
	}
	return (len);
}

//extracts a single segment from position start in str s
//segments are delimited by :
//	-a variable start ($var)
//	-change in quote context
//returns the number of char processed in str s
int	extract_segment(const char *s, int start, quote_t *q, t_segment **seg_out)
{
	int		len;
	char	*text;
	int		from_var;

	from_var = 0;
	if (is_var_start(&s[start], *q))
	{
		start++;
		if (s[start] == '?')
		{
			text = ft_strdup("?");
			len = 1;
		}
		else
		{
			len = var_len(&s[start]);
			text = ft_substr(s, start, len);
		}
		from_var = 1;
	}

	else
	{
		len = scan_segment_len(s, start, q);
		text = ft_substr(s, start, len);
	}
	if (!text)
		return (-1);
	*seg_out = create_new_segment(text, *q, from_var);
	if (!*seg_out)
		return (-1);
	if (from_var)
		return (len + 1);
	return (len);
}

//for each word :
//	-loop on each char of word
//	-skips quotes according to quote context (sq in dq cont and dq in sq cont)
//	-extracts each segments, put it in seg array, go forward in str word
static int	parse_loop(const char *str, t_segment **seg)
{
	int		i;
	int		j;
	int		ret;
	quote_t	q;

	i = 0;
	j = 0;
	q = QUOTE_NONE;
	while (str[i])
	{
		skip_standalone_quotes(str, &i, &q);
		if (!str[i])
			break ;
		ret = extract_segment(str, i, &q, &seg[j]);
		if (ret == -1)
			return (-1);
		i += ret;
		j++;
	}
	seg[j] = NULL;
	return (0);
}

//parses each segments in word, returns array of segments
t_segment	**parse_segments(const char *str)
{
	t_segment	**seg;
	int			max;

	max = ft_strlen(str) + 1;
	seg = malloc(sizeof(t_segment *) * max);
	if (!seg)
		return (NULL);
	if (parse_loop(str, seg) == -1)
		return (free_segments(seg), NULL);
	return (seg);
}
