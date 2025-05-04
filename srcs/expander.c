/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:58 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/04 12:24:59 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_expansion(char *str, char *pcdr, char *val, size_t type)
{
	char	*str_head;
	char	*vnil_str;

	str_head = ft_substr(str, 0, pcdr - str);
	if (!str_head)
		put_err("Expand : Failled to alloc memory for str_head;");
	vnil_str = str;
	if (type == TYPE_DLRS)
		str = ft_strjoin2(str_head, val, pcdr + varsiz(pcdr + 1) + 1);
	else if (type == TYPE_WCRD)
		str = ft_strjoin2(str_head, val, pcdr + pathsiz(pcdr));
	free(str_head);
	free(val);
	free(vnil_str);
	if (!str)
		put_err("Expand : Failled to alloc memory for expanded str;");
	return (str);
}

static char	*eval_placeholder(char *str, char *pcdr_pos, size_t type)
{
	char	*values;
	char	*pcdr;

	if (type == TYPE_DLRS)
		pcdr = ft_substr(pcdr_pos, 1, varsiz(pcdr_pos + 1));
	else if (type == TYPE_WCRD)
		pcdr = ft_substr(pcdr_pos, 0, pathsiz(pcdr_pos));
	if (!pcdr)
		put_err("Expander : Failled to malloc for $pcdr");
	if (type == TYPE_DLRS)
		values = get_envvar(pcdr);
	else if (type == TYPE_WCRD)
		values = get_path(pcdr);
	free(pcdr);
	if (!values)
		values = ft_strdup("");
	if (!values)
		put_err("Expand : Failled to alloc memory for var content;");
	return (concat_expansion(str, pcdr_pos, values, type));
}

#define CHR_SQUOTE '\''
#define CHR_DQUOTE '\"'
//Called when quotes encountered and returns a pointer + 1 to where they end. 
//Same for unmatched quotes
//If $ found while skipping, expand is called
static char	*skip_quotes(char *str, size_t *i, size_t flag)
{
	char	*qts_start;
	char	*qts_end;
	char	*pcdr_pos;

	(void)flag;
	while (1)
	{
		qts_start = str + *i;
		qts_end = ft_strchr(qts_start + 1, qts_start[0]);
		if (!qts_end)
			return (++*i, str);
		pcdr_pos = ft_strnstr(qts_start, "$", qts_end - qts_start);
		if (qts_start[0] == CHR_DQUOTE && pcdr_pos)
			str = eval_placeholder(str, pcdr_pos, flag);
		else
			break ;
	}
	*i += qts_end - qts_start;
	return (str);
}

/*Heredoc content must be treated litteraly, except when their delimiter is
not surrounded by quotes; No * filename expand for herdoc regardless */
char	*expand(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == CHR_SQUOTE || buff[i] == CHR_DQUOTE)
			buff = skip_quotes(buff, &i, TYPE_DLRS);
		if (buff[i] == '$')
		{
			if (ft_strncmp(&buff[i], "$?", ft_strlen(buff + i)) == 0)
				i += 2;
			else
				buff = eval_placeholder(buff, buff + i, TYPE_DLRS);
		}
		else if (buff[i] == '*')
		{
			while (i > 0 && buff[i] != ' ')
				i--;
			buff = eval_placeholder(buff, buff + i, TYPE_WCRD);
		}
		else
			i++;
	}
	return (strip_outquotes(buff));
}
