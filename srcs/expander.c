/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:58 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 00:41:38 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Extract the placeholder depending on its type
//Fetches the corresponding value(s)
//Returns the original string with expanded values
static char	*eval_placeholder(char *str, char *pcdr_pos, size_t type)
{
	char	*values;
	char	*pcdr;

	values = NULL;
	pcdr = NULL;
	if (type == TYPE_DLRS)
		pcdr = ft_substr(pcdr_pos, 1, varsiz(pcdr_pos + 1));
	else if (type == TYPE_WCRD)
		pcdr = ft_substr(pcdr_pos, 0, pathsiz(pcdr_pos));
	if (!pcdr)
		put_err("Expander : Failled to malloc for $pcdr");
	if (type == TYPE_DLRS)
		values = get_envvar(pcdr);
	else if (type == TYPE_WCRD)
		return ((char *)get_path(pcdr));
	free(pcdr);
	if (!values)
		values = chkalloc(ft_strdup(""), "Expander : Malloc Faillure");
	return (concat_expansion(str, pcdr_pos, values, type));
}

static char	*get_exitcode(char *str, char *pcdr_pos)
{
	char	*exitcode;

	exitcode = ft_itoa(g_getset(NULL)->last_exitcode);
	if (!exitcode)
		put_err("Expand : Failled to alloc memory for exitcode;");
	str = concat_expansion(str, pcdr_pos, exitcode, TYPE_CODE);
	return (str);
}

//Skips quotes in original *str by modifying *i index
//If $ found within dquotes, expand is called and *str is updated
static char	*skip_quotes(char *str, size_t *i, size_t flag)
{
	char	*qts_start;
	char	*qts_end;
	char	*pcdr_pos;

	while (1)
	{
		qts_start = str + *i;
		qts_end = ft_strchr(qts_start + 1, qts_start[0]);
		if (!qts_end)
			return (++*i, str);
		pcdr_pos = ft_strnstr(qts_start, "$", qts_end - qts_start);
		if (!pcdr_pos || qts_start[0] == CHR_SQTE)
			break ;
		else if (qts_start[0] == CHR_DQTE && ft_strncmp(pcdr_pos, "$?", 2) == 0)
			str = get_exitcode(str, pcdr_pos);
		else if (qts_start[0] == CHR_DQTE)
			str = eval_placeholder(str, pcdr_pos, flag);
	}
	*i += qts_end - qts_start + 1;
	return (str);
}

//	——— Wildcards EXPANSION SPECIFICS ———
//Wildcards in redirs will generate an error and exit the shell
//Wildcards in var' values will be skipped
//Wildcards in args will generate a new char **args 
//	from the obtained paths and the old args 
static char	*root_wcrd_xpd(char *buff, size_t *i, size_t flag, size_t *status)
{
	if (flag == XPD_REDIR)
		return (ft_dprintf(STDERR_FILENO, "%s: %s", SHELL_NAME, buff),
			put_err(": ambiguous redirect"), NULL);
	else if (flag == XPD_ASSIGN)
		return ((*i)++, *status = XPD_STAT_DFL, buff);
	else if (flag == XPD_ARGS)
	{
		while (*i > 0 && buff[*i] != ' ')
			(*i)--;
		return (*status = XPD_STAT_WCRD,
			eval_placeholder(buff, buff + *i, TYPE_WCRD));
	}
	else
		return (put_err("Expand err: Unknown expand context"), NULL);
}

//	——— HEREDOC EXPANSION SPECIFICS ———
//- Upper caller will prevent calling expand() if heredoc' delimiter included 
// one or more quote; therefore preserving the litteral value of its content
//- Heredocs' quotes are always preserved
//- Heredocs never get globbing / file expansion (*)
char	*expand(char *buff, size_t flag, size_t *status)
{
	size_t	i;

	i = 0;
	while (buff[i])
	{
		if (flag != XPD_HDOC && (buff[i] == CHR_SQTE || buff[i] == CHR_DQTE))
			buff = skip_quotes(buff, &i, TYPE_DLRS);
		else if (ft_strncmp(buff + i, "$?", 2) == 0)
			buff = get_exitcode(buff, buff + i);
		else if (buff[i] == '$' && (varsiz(&buff[i + 1])))
			buff = eval_placeholder(buff, buff + i, TYPE_DLRS);
		else if (buff[i] == '*' && flag != XPD_HDOC)
		{
			if (flag == XPD_ASSIGN)
				buff = root_wcrd_xpd(buff, &i, flag, status);
			else
				return (*status = XPD_STAT_WCRD,
					root_wcrd_xpd(buff, &i, flag, status));
		}
		else
			i++;
	}
	return (*status = XPD_STAT_DFL, buff);
}
