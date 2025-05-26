/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:12:29 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/26 22:14:09 by epinaud          ###   ########.fr       */
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

#define NO_MATCH 0
#define MATCH 1

int	match_pattern(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (MATCH);
			while (*filename)
				if (match_pattern(pattern, filename++))
					return (MATCH);
			return (NO_MATCH);
		}
		else if (*pattern == *filename)
		{
			pattern++;
			filename++;
		}
		else
			return (NO_MATCH);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*filename);
}

char	*get_envvar(char *varname)
{
	char		*match;
	char		**full_var;
	t_minishell	*mshell;

	mshell = g_getset(NULL);
	if (!varname)
		put_err("Expand : Failled to alloc memory for varname;");
	match = ft_lststrn(mshell->var_env, varname, ft_strlen(varname));
	if (!match)
		match = ft_lststrn(mshell->var_shell, varname, ft_strlen(varname));
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

//Soon to be Forsaken util since it has arisen wildcard expansion 
//requires tokenizing each file path as its own WORD token
char	*get_path(char *pcdr)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*paths;
	char			*vnil_path;

	paths = chkalloc(ft_strdup(""), "Expander: Malloc Faillure");
	dir = opendir(".");
	if (!dir)
		return (free(paths), put_err("Expander: Malloc Faillure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return (closedir(dir), paths);
		if (match_pattern(pcdr, entry->d_name))
		{
			vnil_path = paths;
			paths = ft_strjoin2(paths, " ", entry->d_name);
			free(vnil_path);
			if (!paths)
				put_err("Expander : Failled to malloc for $path");
		}
	}
}

/* void	get_path(char *pcdr)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*filename;
	t_token			*start;
	t_token			*end;

	//Find starting next->token
	//Remove next->token
	dir = opendir(".");
	if (!dir)
		return (put_err("Expander: Malloc Faillure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return (closedir(dir));
		if (match_pattern(pcdr, entry->d_name))
		{

			chkalloc(malloc(sizeof(t_token)), "Expander: Malloc Faillure");
			filename->value = entry->d_name;

		}
		//last filename .next = end
	}
}
 */