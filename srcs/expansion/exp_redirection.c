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
static int	is_ambiguous(char **files)
{
	if (!files || !files[0])
		return (1);
	if (files[1])
		return (1);
	return (0);
}

int	redir_exp(t_redir *redir)
{
	t_segment	**seg;
	char		*joined;
	char		**files;

	seg = parse_segments(redir->file);
	if (!seg)
		return (1);
	expand_segments(seg);
	joined = concat_segments(seg);
	if (!joined)
		return (free_segments(seg), 1);
	files = ft_split(joined, ' ');
	free(joined);
	if (is_ambiguous(files))
	{
		ft_dprintf(2, "msh: %s: ambiguous redirect\n", redir->file);
		free_segments(seg);
		free_tab((void **)files);
		return (2);
	}
	redir->exp_file = ft_strdup(files[0]);
	free_segments(seg);
	free_tab((void **)files);
	fflush(stdout);
	return (redir->exp_file == NULL);
}

int	expand_redirs(t_ast_node *node)
{
	t_redir	*redir;
	int		ret;

	redir = node->io_streams;
	//printf(expanding redir file=%s\n", redir->file);
	while (redir)
	{
		ret = redir_exp(redir);
		if (ret)
			return (ret);
		redir = redir->next;
	}
	print_redir_list(redir);
	return (0);
}