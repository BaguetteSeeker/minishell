/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_MATCH 0
#define MATCH 1

//returns 0 on each unquoted * character in segments of word
int	is_wildcard_expandable(t_segment **seg)
{
	int	i;
	int	j;

	i = 0;
	while (seg && seg[i])
	{
		if (seg[i]->quote != QUOTE_NONE)
		{
			j = 0;
			while (seg[i]->text[j])
			{
				if (seg[i]->text[j] == '*')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

//recursively matches a pattern string containing wildcards against target str
//	- literal chars must match exactly
//	- '*' matches zero or more chars
//	- multiple '*' are treated as a single '*'
//returns 1 if the pattern matches the entire str string, 0 otherwise
//really cool
int	match_pattern(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (MATCH);
			while (*str)
				if (match_pattern(pattern, str++))
					return (MATCH);
			return (NO_MATCH);
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (NO_MATCH);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*str);
}

//file filtering handler (for norm purposes)
static int	is_valid_match(const char *pattern, struct dirent *entry, int show_hidden)
{
	if (!entry)
		return (0);
	if ((!show_hidden && entry->d_name[0] == '.')
		|| ft_strcmp(entry->d_name, ".") == 0
		|| ft_strcmp(entry->d_name, "..") == 0)
		return (0);
	return (match_pattern(pattern, entry->d_name));
}

//scans current working directory, returns a list of filenames matching a given wildcard expression
//	- uses opendir() and readdir() to iterate over directory entries.
//	- matches entries against the provided pattern using is_valid_match().
//returns NULL-terminated array of matching strings on match, NULL ptr if no match
static char	**scan_directory(const char *pattern, int show_hidden)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**paths;
	size_t			str_count;

	paths = NULL;
	str_count = 0;
	dir = opendir(".");
	if (!dir)
		return (put_err("Expander: Malloc Failure"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (is_valid_match(pattern, entry, show_hidden))
		{
			paths = chkalloc(ft_realloc(paths, sizeof(char *) * (str_count + 2),
					sizeof(char *) * (str_count)), "Expander : Malloc Failure");
			paths[str_count] = chkalloc(ft_strdup(entry->d_name), "Expander : Malloc Failure");
			paths[++str_count] = NULL;
		}
	}
	closedir(dir);
	return (paths);
}

//returns the list of files in current directory matching wildcard expression
char	**get_path(char *pcdr)
{
	char	**paths;
	int		show_hidden;

	show_hidden = (pcdr && pcdr[0] == '.');
	paths = scan_directory(pcdr, show_hidden);
	if (!paths)
	{
		paths = malloc(sizeof(char *) * 2);
		paths[0] = ft_strdup(pcdr);
		paths[1] = NULL;
	}
	return (paths);
}