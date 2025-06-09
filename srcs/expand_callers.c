/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_callers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:53:00 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 13:40:04 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Looks for the DEL char previously inserted right before EOF
//If found, heredoc is expandable, if not, it isn't
//Only overwrites the DEL char once the content is re-expanded during execution,
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

#define XPD_DFL_STATUS 0
//Calls expand on *ptr and returns the resulting buffer
//Also updates the associated *ptr in the token list
static char	*expd_rplctok(char *ptr, size_t flag)
{
	t_token	*tokens;
	size_t	void_status;

	void_status = XPD_DFL_STATUS;
	tokens = g_getset(NULL)->tokens;
	while (tokens)
	{
		if (tokens->value == ptr)
		{
			tokens->value = expand(ptr, flag, &void_status);
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
		stream->file = strip_outquotes(
				expd_rplctok(stream->file, XPD_REDIR));
}

static char	**extend_args(char **args, char *target, char **wcrdarr)
{
	char	**newargs;

	strarr_iter(wcrdarr, (void *)&strip_outquotes);
	newargs = strarr_insert(args, target, wcrdarr);
	put_recurse_dynarr(newargs);
	free(args);
	free(target);
	free(wcrdarr);
	return (newargs);
}

void	expand_node(t_ast_node *node)
{
	size_t	xpd_status;
	char	*new_buff;
	int		i;

	xpd_status = 0;
	i = -1;
	while (node->args && node->args[++i])
	{
		new_buff = expand(node->args[i], XPD_ARGS, &xpd_status);
		if (xpd_status == 0)
			node->args[i] = strip_outquotes(new_buff);
		else
			node->args = extend_args(node->args,
					node->args[i], (char **)new_buff);
	}
	i = -1;
	while (node->vars && node->vars[++i])
		node->vars[i] = strip_outquotes(
				expand(node->vars[i], XPD_ASSIGN, &xpd_status));
	if (node->io_streams)
		msh_lstiter(node->io_streams, &expand_redirs);
}
