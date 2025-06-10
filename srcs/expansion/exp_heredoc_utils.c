/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 15:34:01 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Looks for the DEL char previously inserted right before EOF
//If found, heredoc is expandable, if not, it isn't
//Only overwrites the DEL char once the content is re-expanded during execution,
//otherwise, exit codes in heredoc would remain litteral
bool	is_expandable(char *hdoc)
{
	bool	is_expandable;
	size_t	hdoc_siz;

	hdoc_siz = ft_strlen(hdoc);
	if (hdoc[hdoc_siz - 1] == EXPANDABLE_HEREDOC)
	{
		if (g_getset(NULL)->state == MSH_EXECUTING)
			hdoc[hdoc_siz - 1] = '\0';
		is_expandable = true;
	}
	else
		is_expandable = false;
	return (is_expandable);
}

static int	count_lines(const char *s)
{
	int	count;
	int	i;

	if (!s || !*s)
		return (1);
	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

//joins every lines in a new str
char	*join_lines(char **lines)
{
	char	*joined;
	char	*tmp;
	int		i;

	if (!lines || !lines[0])
		return (ft_strdup(""));
	joined = ft_strjoin(lines[0], "\n");
	if (!joined)
		return (NULL);
	i = 1;
	while (lines[i])
	{
		tmp = ft_strjoin(joined, lines[i]);
		free(joined);
		if (!tmp)
			return (NULL);
		joined = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!joined)
			return (NULL);
		i++;
	}
	return (joined);
}

//ft_split, modified to extract \n\n as a valid word '\0'
char	**split_heredoc(const char *s)
{
	char	**slist;
	int		start;
	int		end;
	int		i;

	slist = malloc(sizeof(char *) * (count_lines(s) + 1));
	if (!slist)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start])
	{
		end = start;
		while (s[end] && s[end] != '\n')
			end++;
		slist[i] = ft_substr(s, start, end - start);
		if (!slist[i++])
			return (ft_free_dynarr(slist));
		if (!s[end])
			break ;
		start = end + 1;
	}
	slist[i] = NULL;
	return (slist);
}
