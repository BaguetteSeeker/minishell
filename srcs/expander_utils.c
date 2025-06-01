/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:12:29 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/01 15:52:22 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	varsiz(const char *var)
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

size_t	pathsiz(const char *path)
{
	size_t	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		if (!(isalnum(path[i]) || ft_strchr("_-./~*", path[i])))
			break ;
		if (i > 0 && path[i] == '/' && path[i - 1] == '/')
			break ;
		i++;
	}
	return (i);
}

//Replaces *pcdr based on type with provided *val within *str
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
	else if (type == TYPE_CODE)
		str = ft_strjoin2(str_head, val, pcdr + 2);
	free(str_head);
	free(val);
	free(vnil_str);
	if (!str)
		put_err("Expand : Failled to alloc memory for expanded str;");
	return (str);
}

char	*get_envvar(char *varname)
{
	char		*match;
	char		**full_var;
	t_minishell	*mshell;

	mshell = g_getset(NULL);
	if (!varname)
		put_err("Expand : Failled to alloc memory for varname;");
	match = ft_lststr(mshell->var_env, varname);
	if (!match)
		match = ft_lststr(mshell->var_shell, varname);
	if (match)
	{
		full_var = ft_split(match, '=');
		if (!full_var)
			put_err("Expand : Failled to alloc memory for full_var;");
		match = full_var[1];
		free(full_var[0]);
		free(full_var);
	}
	return (match);
}

//add entry module
char	**get_path(char *pcdr)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**paths;
	size_t			str_count;

	paths = NULL;
	str_count = 0;
	dir = opendir(".");
	if (!dir)
		return (put_err("Expander: Malloc Faillure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return (free(pcdr), closedir(dir), paths);
		if (match_pattern(pcdr, entry->d_name))
		{
			paths = chkalloc(ft_realloc(paths, sizeof(char *) * (str_count + 2),
						sizeof(char *) * (str_count)),
					"Expander : Malloc Faillure");
			paths[str_count] = chkalloc(ft_strdup(entry->d_name),
					"Expander : Malloc Faillure");
			paths[++str_count] = NULL;
		}
	}
}
