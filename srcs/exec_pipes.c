/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:22:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/18 18:22:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//(SIGPIPE tells kernel to end process that has no reader)
//duplicates the write end of pipe to its std_out
//closes all other end
//goes to the next node in tree
void execute_cmd1(t_ast_node *node, int *pipe_fd)
{
	signal(SIGPIPE, SIG_DFL);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(execute_node(node->left));
}

void execute_cmd2(t_ast_node *node, int *pipe_fd)
{
	signal(SIGPIPE, SIG_DFL);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exit(execute_node(node->right));
}

//creates a pipe and fork the two processes
//close all pipe ends in parent and wait for said processes
//returns the exit status of the right (execute_cmd2) process 
int	execute_pipe(t_ast_node *node)
{
	pid_t	pid_left, pid_right;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
		execute_cmd1(node, pipe_fd);
	pid_right = fork();
	if (pid_right == 0)
		execute_cmd2(node, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}