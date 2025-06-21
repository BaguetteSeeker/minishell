/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:22:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 14:47:05 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//(SIGPIPE tells kernel to end process that has no reader)
//duplicates the write end of pipe to its std_out
//closes all other end
//goes to the next node in tree
void	execute_node1(t_ast_node *node, int *pipe_fd)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGPIPE, SIG_DFL);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_status = execute_node(node->left);
	clean_shell();
	// printf("\n\nprocess 1 exit : %d\n\n", exit_status);
	fflush(stdout);
	exit(exit_status);
}

void	execute_node2(t_ast_node *node, int *pipe_fd)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGPIPE, SIG_DFL);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exit_status = execute_node(node->right);
	clean_shell();
	// printf("\n\nprocess 2 exit : %d\n\n", exit_status);
	fflush(stdout);
	exit(exit_status);
}

//ignores signals in parent
//creates a pipe and fork the two processes
//close all pipe ends in parent and wait for said processes
//restores shell signal handling behavior in parent proc
//returns the exit status of the right (execute_node2) process
int	execute_pipe(t_ast_node *node)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipe_fd[2];
	int		status;
	int		status2;
	int		exit_status;

	set_foreground_flag(node);
	signal(SIGINT, SIG_IGN);
	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_node1(node, pipe_fd);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_node2(node, pipe_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status2, 0);
	signal(SIGINT, signals_handler);
	if (WIFSIGNALED(status2))
		exit_status = 128 + WTERMSIG(status2);
	else
		exit_status = WEXITSTATUS(status2);
	set_exitcode(exit_status);
	return (exit_status);
}


