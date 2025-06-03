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

static int	redir_exp(t_redir *redir)
{
	t_segment	**seg;
	char		*joined;
	char		**files;

	seg = NULL;
	printf("\rfile : %s\n\n", redir->file);
	if (redir->file) //here
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
		ft_dprintf(2, "minishell: %s: ambiguous redirect\n", redir->file);
		free_segments(seg);
		free_tab((void **)files);
		return (clean_shell(), 1);
	}
	redir->exp_file = ft_strdup(files[0]);
	free_segments(seg);
	free_tab((void **)files);
	return (redir->exp_file == NULL);
}

void	print_redir_list(t_redir *redir)
{
	int	i = 0;
	while (redir)
	{
		printf("redir #%d -> file: [%s], type: %d\n", i, redir->file, redir->type);
		redir = redir->next;
		i++;
	}
}


int	expand_redirs(t_ast_node *node)
{
	t_redir	*redir;

	redir = node->io_streams;
	print_redir_list(redir);
	fflush(stdout);
	while (redir)
	{
		printf("iterating\n");
		fflush(stdout);

		if (redir_exp(redir))
			return (1);
		redir = redir->next;
	}
	print_redir_list(redir);
	return (0);
}