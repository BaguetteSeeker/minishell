/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:58 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/04 00:27:14 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_outquotes(char *str)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strchr("\"\'", str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (str);
}

static size_t	ft_varsiz(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
	{
		if (i == 0 && ft_isdigit(var[i]))
			break ;
		i++;
	}
	return (i);
}

static size_t	check_pathname(const char *path)
{
    size_t	i;

    if (!path)
        return (0);
    i = 0;
    while (path[i])
    {
        // Valid characters: alphanumeric, '_', '-', '.', '/', and '~'
        if (!(isalnum(path[i]) || path[i] == '_' || path[i] == '-' ||
              path[i] == '.' || path[i] == '/' || path[i] == '~' || path[i] == '*'))
            break;
        // Consecutive '/' are not allowed (except at the start)
        if (i > 0 && path[i] == '/' && path[i - 1] == '/')
            break;
        i++;
    }
    return (i);
}

char	*concat_expansion(char *str, char *pcdr, char *val, size_t type)
{
	char	*str_head;
	char	*vnil_str;

	str_head = ft_substr(str, 0, pcdr - str);
	if (!str_head)
		put_err("Expand : Failled to alloc memory for str_head;");
	vnil_str = str;
	if (type == TYPE_DLRS)
		str = ft_strjoin2(str_head, val, pcdr + ft_varsiz(pcdr + 1) + 1);
	else if (type == TYPE_WCRD)
		str = ft_strjoin2(str_head, val, pcdr + check_pathname(pcdr));
	free(str_head);
	free(val);
	free(vnil_str);
	if (!str)
		put_err("Expand : Failled to alloc memory for expanded str;");
	return (str);
}

char	*eval_placeholder(char *str, char *pcdr, size_t type)
{
	char	*values;

	if (type == TYPE_DLRS)
		values = get_envvar(pcdr, ft_varsiz(pcdr + 1));
	else if (type == TYPE_WCRD)
		values = get_path(pcdr, check_pathname(pcdr));
	if (!values)
		values = ft_strdup("");
	if (!values)
		put_err("Expand : Failled to alloc memory for var content;");
	//varsiz only computes size for $VAR placeholders
	return (concat_expansion(str, pcdr, values, type));
}

#define SQUOTE '\''
#define DQUOTE '\"'
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
		if (qts_start[0] == DQUOTE && pcdr_pos)
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
		if (buff[i] == SQUOTE || buff[i] == DQUOTE)
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
			i += check_pathname(buff);
		}
		else
			i++;
	}
	return (strip_outquotes(buff));
}
