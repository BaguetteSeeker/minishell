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

// on this function, the shell should handle a missing exp_file
int	redir_in(t_redir	*redir)
{
	int		fd;

	if (access(redir->exp_file, F_OK) != 0 || access(redir->exp_file, R_OK) != 0)
		return (perror(redir->exp_file), 1);
	fd = open(redir->exp_file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->exp_file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_out(t_redir	*redir)
{
	int		fd;

	fd = open(redir->exp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->exp_file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	heredoc(t_redir	*redir)
{
	int	fds[2];

	if (pipe(fds) < 0)
		return (perror("heredoc pipe"), 1);
	write(fds[1], redir->exp_file, ft_strlen(redir->exp_file));
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	return (0);
}

int	redir_append(t_redir	*redir)
{
	int		fd;

	fd = open(redir->exp_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->exp_file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
//explore the linked list of redirections
//on failure, returns edequate exit code
//if multiple redirection of same fd, last one prevales
int	redirections_handler(t_ast_node *node)
{
	int		exit_code;
	t_redir	*redir;

	exit_code = 0;
	redir = node->io_streams;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			exit_code =redir_in(redir);
		else if (redir->type == REDIR_OUT)
			exit_code =redir_out(redir);
		else if (redir->type == HEREDOC)
			exit_code =heredoc(redir);
		else if (redir->type == APPEND)
			exit_code =redir_append(redir);
		redir = redir->next;
	}
	return (exit_code);
}
