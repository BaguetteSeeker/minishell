/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:22:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/18 18:22:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// on this function, the shell should handle a missing file
//return value should be 1
void	redir_in(t_redir	*redir)
{
	int		fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file));
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_out(t_redir	*redir)
{
	int		fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc(t_redir	*redir)
{
	int	fds[2];

	if (pipe(fds) < 0)
		return (perror("heredoc pipe"));
	write(fds[1], redir->file, ft_strlen(redir->file));
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

void	redir_append(t_redir	*redir)
{
	int		fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

//TO FIX :
//must be able to return errors and stop execution on a failed redirection
//(it isn't right now)
//int redirections_handler(t_ast_node *node)
//(returns 0 on sucess, 1 on failure)
void	redirections_handler(t_ast_node *node)
{
	t_redir	*redir;

	redir = node->io_streams;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			redir_in(redir);
		else if (redir->type == REDIR_OUT)
			redir_out(redir);
		else if (redir->type == HEREDOC)
			heredoc(redir);
		else if (redir->type == APPEND)
			redir_append(redir);
		redir = redir->next;
	}
}
