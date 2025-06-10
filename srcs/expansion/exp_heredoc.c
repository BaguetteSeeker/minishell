/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 16:53:13 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_seg_quote(char	*str, char qc)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!new_str)
		perror("malloc error");
	new_str[i] = qc;
	i++;
	while (str[j] != '\0')
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = qc;
	i++;
	new_str[i] = '\0';
	return (new_str);
}

void	addback_quote(t_segment **seg)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (seg[i])
	{
		if (seg[i]->quote == QUOTE_NONE)
		{
			i++;
			continue ;
		}
		if (seg[i]->quote == QUOTE_DOUBLE)
			str = new_seg_quote(seg[i]->text, '\"');
		else if (seg[i]->quote == QUOTE_SINGLE)
			str = new_seg_quote(seg[i]->text, '\'');
		if (str)
		{
			free(seg[i]->text);
			seg[i]->text = str;
		}
		i++;
	}
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
	addback_quote(segments);
	expanded = concat_segments(segments);
	free_segments(segments);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
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
