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

//Looks for the DEL char previously inserted right before EOF
//If found, heredoc is expandable, if not, it isn't
//Only overwrites the DEL char once the content is re-expanded during execution,
//otherwise, exit codes in heredoc would remain litteral 
static bool	is_expandable(char *hdoc)
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

//uses the same logic as normal variable expansion
//no word splitting or wildcard expansion
//return "" if expands to nothing
static char	*expand_line(const char *line)
{
	t_segment	**segments;
	char		*expanded;

	if (!line)
		return (NULL);
	segments = parse_segments(line);
	if (!segments)
		return (NULL);
	expand_segments(segments);
	expanded = concat_segments(segments);
	free_segments(segments);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}

//joins every lines in a new str
static char	*join_lines(char **lines)
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

//expands each line using segmentation logic (helper for norm)
static char	**expand_heredoc_lines(char **lines)
{
	char	**out;
	char	*new_line;
	int		i;

	out = malloc(sizeof(char *) * (ft_ptrlen((const void **)lines) + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (lines[i])
	{
		new_line = expand_line(lines[i]);
		if (new_line == NULL)
		{
			while (i-- > 0)
				free(out[i]);
			free(out);
			return (NULL);
		}
		out[i] = new_line;
		i++;
	}
	out[i] = NULL;
	return (out);
}

//expands a heredoc's content if it was marked as expandable.
//	-Splits the content into lines.
//	-Expands variables on each line (but not wildcards or word splitting).
//	-Joins the expanded lines into a single string with '\n' separators.
//	-Stores the result in `redir->exp_file`.
int	heredoc_exp(t_redir *redir)
{
	char	**lines;
	char	**expanded;
	char	*joined;

	if (!redir || !redir->file || !is_expandable(redir->file))
	{
		redir->exp_file = ft_strdup(redir->file);
		return (0);
	}
	lines = split_heredoc(redir->file);
	if (!lines)
		return (1);
	expanded = expand_heredoc_lines(lines);
	free_tab((void **)lines);
	if (!expanded)
		return (1);
	joined = join_lines(expanded);
	free_tab((void **)expanded);
	if (!joined)
		return (1);
	redir->exp_file = joined;
	return (0);
}
