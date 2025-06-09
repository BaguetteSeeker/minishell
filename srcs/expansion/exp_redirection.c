/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirection is considered ambiguous if multiple words are defined in
//words (after splitting) delimited as unquoted spaces in segments
static int	is_redir_ambiguous(t_segment **seg)
{
	int	i;
	int	has_space;
	int	unquoted_count;

	i = 0;
	has_space = 0;
	unquoted_count = 0;
	while (seg[i])
	{
		if (seg[i]->quote == QUOTE_NONE)
		{
			unquoted_count++;
			if (contains_unquoted_space(seg[i]))
				has_space = 1;
		}
		i++;
	}
	return (unquoted_count > 1 || has_space);
}

//expands redirection token using segmentation logic, word-aware
//parse seg from word, expand them, check if unquote space, concat
int	redir_exp(t_redir *redir)
{
	t_segment	**seg;
	char		*joined;

	seg = parse_segments(redir->file);
	if (!seg)
		return (1);
	expand_segments(seg);
	if (is_redir_ambiguous(seg))
	{
		ft_dprintf(2, "msh: %s: ambiguous redirect\n", redir->file);
		free_segments(seg);
		return (2);
	}
	joined = concat_segments(seg);
	if (!joined)
		return (free_segments(seg), 1);
	redir->exp_file = ft_strdup(joined);
	free(joined);
	free_segments(seg);
	return (redir->exp_file == NULL);
}

// //Looks for the DEL char previously inserted right before EOF
// //If found, heredoc is expandable, if not, it isn't
// //Only overwrites the DEL char once the content is re-expanded during execution,
// //otherwise, exit codes in heredoc would remain litteral 
// static bool    is_expandable(char *hdoc)
// {
//     bool    is_expandable;
//     size_t    hdoc_siz;

//     hdoc_siz = ft_strlen(hdoc);
//     if (hdoc[hdoc_siz - 1] == EXPANDABLE_HEREDOC)
//     {
//         if (g_getset(NULL)->state == MSH_EXECUTING)
//             hdoc[hdoc_siz - 1] = '\0';
//         is_expandable = true;
//     }
//     else
//         is_expandable = false;
//     return (is_expandable);
// }

// int	heredoc_exp(t_redir)
// {

// }

int	expand_redirs(t_ast_node *node)
{
	t_redir	*redir;
	int		ret;

	redir = node->io_streams;
	while (redir)
	{
		ret = redir_exp(redir);
		if (ret)
			break ;
		redir = redir->next;
	}
	return (ret);
}
