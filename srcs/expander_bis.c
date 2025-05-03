/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:12:29 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/04 00:38:29 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
char	*delim_pathname(char *str, char *card_pos)
{
	char	*pathname;

	while (card_pos != str && *card_pos != '/')
		card_pos--;
		pathname = ft_substr(str, 0, card_pos - str);
		if (!pathname)
			put_err("Failled to alloc mem for pathname");
		if (ft_strchr(pathname, '*'))
		{
			ft_bzero(pathname, sizeof(*pathname) * ft_strlen(pathname));
			pathname[0] = '.';
		}

	return (pathname);
}
*/

#define NO_MATCH 0
#define MATCH 1
int match_pattern(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (MATCH); // Match if '*' is the last character
			while (*filename)
			{
				if (match_pattern(pattern, filename))
					return (MATCH);
				filename++;
			}
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

//Searches for strlen(str) char the string str in the dynamic array lst
static char	*ft_lststrn(char **lst, char *str)
{
	int		i;
	size_t	strlen;

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


char	*get_envvar(char *varname, size_t varsiz)
{
	char	*match;
	char	**full_var;

	varname = ft_substr(varname, 1, varsiz);
	if (!varname)
		put_err("Expand : Failled to alloc memory for varname;");
	match = ft_lststrn(g_getset(NULL)->var_env, varname);
	if (!match)
		match = ft_lststrn(g_getset(NULL)->var_shell, varname);
	if (match)
	{
		// match = ft_strdup(match);
		// if (!match)
		// 	put_err("Expand : Failled to alloc memory for varvalue;");
		full_var = ft_split(match, '=');
		if (!full_var)
			put_err("Expand : Failled to alloc memory for full_var;");
		match = full_var[1];
		free(full_var[0]);
		free(full_var);
	}
	free(varname);
	return (match);
}

////!!!! get rid of the trailing space
char	*get_path(char *pcdr, size_t pathsiz)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*paths;
	
	paths = ft_strdup("");
	if (!paths)
		put_err("Expander : Failled to malloc for $path");
	pcdr = ft_substr(pcdr, 0, pathsiz);
	if (!pcdr)
		put_err("Expander : Failled to malloc for $pcdr");
	dir = opendir(".");
	if (!dir)
		put_err("Expander: failled to open directory");
	ft_putendl_fd("Current dir contains :\n", 1);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (match_pattern(pcdr, entry->d_name))
		{
			ft_printf("Match -> %s\n", entry->d_name);
			paths = ft_strjoin2(paths, " ", entry->d_name);
			if (!paths)
				put_err("Expander : Failled to malloc for $path");
		}
	}
	free(pcdr);
	closedir(dir);
	return (paths);
}
