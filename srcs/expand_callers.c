/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_callers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:53:00 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/25 17:45:13 by epinaud          ###   ########.fr       */
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
		stream->file = expand(stream->file, XPD_HDOC);
	else if (stream->type != HEREDOC)
		stream->file = expand(stream->file, XPD_REDIR);
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
	msh_lstiter(node->io_streams, &expand_redirs);
}

void	expand_token(t_token *tokens)
{
	static int	last_token = -1;

	if (tokens->type == WORD)
	{
		if (last_token == DLESS)
		{
			if (is_expandable(tokens->value))
				tokens->value = expand(tokens->value, XPD_HDOC);
		}
		else if (in_array(last_token, (int []){LESS, GREAT, DGREAT}, 3))
			tokens->value = expand(tokens->value, XPD_REDIR);
		else
			tokens->value = strip_outquotes(expand(tokens->value, XPD_ALL));
	}
	last_token = tokens->type;
}
