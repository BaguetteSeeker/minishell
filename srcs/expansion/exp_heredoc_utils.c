/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
