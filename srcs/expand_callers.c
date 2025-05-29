/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_callers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:53:00 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 18:30:08 by epinaud          ###   ########.fr       */
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

//Calls expand on *ptr and returns the resulting buffer
//Also updates the associated *ptr in the token list
static char	*expd_rplctok(char *ptr, size_t flag)
{
	t_token	*tokens;

	tokens = g_getset(NULL)->tokens;
	while (tokens)
	{
		if (tokens->value == ptr)
		{
			tokens->value = expand(ptr, flag);
			break ;
		}
		tokens = tokens->next;
	}
	return (tokens->value);
}

static void	expand_redirs(t_redir *stream)
{
	if (stream->type == HEREDOC && is_expandable(stream->file))
		stream->file = expd_rplctok(stream->file, XPD_HDOC);
	else if (stream->type != HEREDOC)
		stream->file = strip_outquotes(expd_rplctok(stream->file, XPD_REDIR));
}

void	expand_node(t_ast_node *node)
{
	int	i;

	i = -1;
	while (node->args && node->args[++i])
		node->args[i] = strip_outquotes(expd_rplctok(node->args[i], XPD_ALL));
	i = -1;
	while (node->vars && node->vars[++i])
		node->vars[i] = strip_outquotes(expd_rplctok(node->vars[i], XPD_ALL));
	if (node->io_streams)
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
			tokens->value = strip_outquotes(expand(tokens->value, XPD_REDIR));
		else
			tokens->value = strip_outquotes(expand(tokens->value, XPD_ALL));
	}
	last_token = tokens->type;
}
