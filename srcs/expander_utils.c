/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:12:29 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 00:03:23 by epinaud          ###   ########.fr       */
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

char	*get_path(char *pcdr)
{
	DIR			 	*dir;
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

/* char	*lst_injectreplace(char *val_tofind, t_token *newlst)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	prev = NULL;
	curr = g_getset(NULL)->tokens;
	// Find the token to replace and its previous node
	while (curr && curr->value != val_tofind)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		put_err("Lst val not found");
	next = curr->next;
	lstdelone_tokens(curr, free_token_value);
	// Insert newlst at the position of curr or define new head
	if (prev)
		prev->next = newlst;
	else
		g_getset(NULL)->tokens = newlst;
	lstlast_tokens(newlst)->next = (t_list *)next;
	return (next ? newlst->value : NULL);
}

char	*get_path(char *pcdr)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*paths;
	t_token			*path;

	path = NULL;
	paths = NULL;
	dir = opendir(".");
	if (!dir)
		return (put_err("Expander: Malloc Faillure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return (closedir(dir), lst_injectreplace(pcdr, path));
		if (match_pattern(pcdr, entry->d_name))
		{
			path = chkalloc(malloc(sizeof(t_token)), 
				"Expander: Malloc Faillure");
			*path = (t_token){0};
			path->value = ft_strdup(entry->d_name);
			if (!path->value)
				put_err("Expander: Malloc Faillure");
			lstadd_back_tokens(&paths, path);
		}
	}
} */
