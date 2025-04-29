/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:34:58 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/29 12:44:18 by epinaud          ###   ########.fr       */
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

//Searches for strlen(str) char the string str in the dynamic array lst
char	*ft_lststrn(char **lst, char *str)
{
	int		i;
	size_t	strlen;

	//TODO:Remove this check once shell vars has been properly populated
	if (!lst)
		return (NULL);
	i = 0;
	strlen = ft_strlen(str);
	while (lst[i])
	{
		if (ft_strncmp(str, lst[i], strlen) == 0)
			return (lst[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_varsiz(char *var);

size_t	ft_varsiz(char *var)
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

static char	*get_envvar(char *varname)
{
	char	*match;
	char	**full_var;

	varname = ft_substr(varname, 1, ft_varsiz(varname + 1));
	if (!varname)
		put_err("Expand : Failled to alloc memory for varname;");
	//what if env and shell both contains the same variable ?
	match = ft_lststrn(g_getset(NULL)->var_env, varname);
	if (!match)
		match = ft_lststrn(g_getset(NULL)->var_shell, varname);
	if (match)
	{
		match = ft_strdup(match);
		if (!match)
			put_err("Expand : Failled to alloc memory for varvalue;");
		full_var = ft_split(match, '=');
		free(match);
		if (!full_var)
			put_err("Expand : Failled to alloc memory for full_var;");
		match = full_var[1];
		free(full_var[0]);
		free(full_var);
	}
	free(varname);
	return (match);
}

char	*eval_placeholder(char *str, char *pcdr)
{
	char	*str_head;
	char	*values;
	// char	*vnil_str;
	
	// vnil_str = str;
	str_head = ft_substr(str, 0, pcdr - str);
	if (!str_head)
		put_err("Expand : Failled to alloc memory for str_head;");
	if (*pcdr == '$')
		values = get_envvar(pcdr);
	else if (*pcdr == '*') //Wont work in some cases as * exp sometimes imply a preceeding path
		return (NULL);
	if (!values)
		values = ft_strdup("");
	if (!values)
		put_err("Expand : Failled to alloc memory for var content;");
	//varsiz only computes size for $VAR placeholders
	str = ft_strjoin2(str_head, values, pcdr + ft_varsiz(pcdr + 1) + 1);
	free(str_head);
	free(values);
	//free(vnil_str);
	if (!str)
		put_err("Expand : Failled to alloc memory for expanded str;");
	return (str);
}

#define SQUOTE '\''
#define DQUOTE '\"'
//Called when quotes encountered and returns a pointer + 1 to where they end. 
//Same for unmatched quotes
//If $ found while skipping, expand is called, 
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
			str = eval_placeholder(str, pcdr_pos);
		else
			break ;
	}
	*i += qts_end - qts_start;
	return (str);
}

/* ************************************************************************** */
/* 

#define EXP_ERR_CODE
Heredoc content must be treated litteraly, except when their delimiter is
not surrounded by quotes; No * filename expand for herdoc regardless */
char	*expand(char *buff, size_t mode)
{
	size_t	i;
	(void)mode;

	i = 0;
	//trim semantic quotes
	while (buff[i])
	{
		if (buff[i] == SQUOTE || buff[i] == DQUOTE)
			buff = skip_quotes(buff, &i, 0);
		if (buff[i] == '$')
		{
			if (ft_strncmp(&buff[i], "$?", ft_strlen(buff + i)) == 0)
				i += 2;
			else
				buff = eval_placeholder(buff, buff + i);
		}
		// else if (buff[i] == '*')
		// 	buff = append_filenames();
		else
			i++;
	}
	return (strip_outquotes(buff));
}