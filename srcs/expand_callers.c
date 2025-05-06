/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_callers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:53:00 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/06 18:59:08 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_expandable(char *hdoc)
{
	bool	is_expandable;
	size_t	hdoc_siz;

	hdoc_siz = ft_strlen(hdoc);
	if (hdoc[hdoc_siz - 1] == EXPANDABLE_HEREDOC)
	{
		hdoc[hdoc_siz - 1] = '\0';
		is_expandable = true;
	}
	else
		is_expandable = false;
	return (is_expandable);
}

static void	expand_redirs(t_redir *stream)
{
	if (stream->type == HEREDOC && is_expandable(stream->file))
		stream->file = expand(stream->file, XPD_HDOC_VARS);
	else if (stream->type != HEREDOC)
		stream->file = expand(stream->file, XPD_ALL);
}

void	expand_node(t_ast_node *node)
{
	int	i;

	i = -1;
	node->value = expand(node->value, XPD_ALL);
	while (node->args[++i])
		node->args[i] = expand(node->args[i], XPD_ALL);
	i = -1;
	while (node->vars[++i])
		node->vars[i] = expand(node->vars[i], XPD_ALL);
	lstiter_redirs(node->io_streams, &expand_redirs);
}

void	expand_token(t_token *tokens)
{
	static size_t	found_heredoc = 0;

	if (tokens->type == DLESS)
		found_heredoc = 1;
	else if (tokens->type == WORD)
	{
		if (found_heredoc && is_expandable(tokens->value))
			tokens->value = expand(tokens->value, XPD_HDOC_VARS);
		else if (!found_heredoc)
			tokens->value = strip_outquotes(expand(tokens->value, XPD_ALL));
		found_heredoc = 0;
	}
}
