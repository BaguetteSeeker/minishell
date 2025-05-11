/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidi <sidi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:56:17 by souaret           #+#    #+#             */
/*   Updated: 2025/05/11 14:03:30 by sidi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork2(t_cmd *cmd);

/************************************************************************
 * 
 * 
 * TODO: review this  formula of the pipe preparation
************************************************************************/
/*
void	ft_prepare_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe");
		do_error_exit(EXIT_FAILURE);
	}
	if (cmd->left->file_out != STDOUT_FILENO)
	{
		close(cmd->left->file_out);
		cmd->left->file_out = cmd->pipe_fd[1];
	}
	if (cmd->right->file_in != STDIN_FILENO)
	{
		close(cmd->right->file_in);
		cmd->right->file_in = cmd->pipe_fd[0];
	}
}
*/

void	ft_prepare_pipe(t_cmd *cmd, int pos, int fd[2])
{
	(void) cmd;
	if (pos == NODE_LEFT)
	{
		close(fd[0]); 
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[1]);
	}
	else
	{
		close(fd[1]); 
		dup2(fd[0], STDIN_FILENO); 
		close(fd[0]);
	}
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
int	ft_fork_node_pipe(t_cmd *node, int pos, int fd[2])
{
	int	pid;
	int	status;

	pid = ft_fork(node);
	do_check_error_exit((pid == -1), EXIT_FAILURE);
	if (pid == 0)
	{
		if (pos == NODE_LEFT)
		{
			// close(fd[0]); dup2(fd[1], STDOUT_FILENO); close(fd[1]);
			ft_close_fd(&fd[0]);
			ft_dup2(&fd[1], STDOUT_FILENO);
			ft_close_fd(&fd[1]);
		}
		else
		{
			//close(fd[1]); dup2(fd[0], STDIN_FILENO); close(fd[0]);
			ft_close_fd(&fd[1]);
			ft_dup2(&fd[0], STDIN_FILENO);
			ft_close_fd(&fd[0]);

		}
		status = cmd_exe_node(node);
		free_and_exit(status);
	}
	return (pid);
}

int	ft_fork_node_pipe2(t_cmd *node, int pos, int fd[])
{
	int	pid;
	int	status;

	pid = ft_fork2(node);
	do_check_error_exit((pid == -1), EXIT_FAILURE);
	if (pid == 0)
	{
		if (pos == NODE_LEFT)
		{
			// close(fd[0]); dup2(fd[1], STDOUT_FILENO); close(fd[1]);
			ft_close_fd(&fd[0]);
			ft_dup2(&fd[1], STDOUT_FILENO);
			ft_close_fd(&fd[1]);
		}
		else
		{
			//close(fd[1]); dup2(fd[0], STDIN_FILENO); close(fd[0]);
			ft_close_fd(&fd[1]);
			ft_dup2(&fd[0], STDIN_FILENO);
			ft_close_fd(&fd[0]);

		}
		status = cmd_exe_node(node);
		free_and_exit(status);
	}
	return (pid);
}
/************************************************************************
 * 
 * close pipe flows, and reset file descriptors to default values
 * 
 * TODO: Review this code & test behavior
************************************************************************/
void	ft_close_pipe_flows(t_cmd *cmd, int fd[2])
{
	(void) cmd;
	ft_close_fd(&fd[1]);
	ft_close_fd(&fd[0]);
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
/*
int	cmd_exe_pipe(t_cmd *cmd)
{
	int	fd[2];
	int	pid[2];
	int	status;

	(void) status;
	(void) pid;
	(void) fd;
	cmd_exe_pipe2(cmd);

	ft_dprintf(STDERR_FILENO, "Executing | : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_dprintf(STDERR_FILENO, "*** Error:  | needs two operands\n");
		return (-1); // error
	}
	// ft_prepare_pipe(cmd);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		do_error_exit(EXIT_FAILURE);
	}
	
	pid[0] = ft_fork_node_pipe2(cmd->left, NODE_LEFT, fd);
	pid[1] = ft_fork_node_pipe(cmd->right, NODE_RIGHT, fd);
	ft_close_pipe_flows(cmd, fd);
	if (ft_waitpid(pid[0]) == -1)
	{
		perror("waitpid");
		do_error_exit(EXIT_FAILURE);
	}
	if (ft_waitpid(pid[1]) == -1)
	{
	 	perror("waitpid");
	 	do_error_exit(EXIT_FAILURE);
	}
	status = get_status();
	ft_dprintf(STDERR_FILENO, "status: <%d>\n", status);
	return (get_status());
}
*/


/************************************************************************/
int	cmd_exe_pipe2(t_cmd *cmd)
{
    int pipefd[2];
    pid_t pid[2];

    ft_pipe(pipefd);
	pid[0] = ft_fork(cmd->left);
	if (pid[0] == 0)
	{
		ft_prepare_pipe(cmd->left, NODE_LEFT, pipefd);
		//TODO:  This is a work-arround, need to chek if it's a cmd or a node
		//	initially : status = cmd_exe_node(node);
		cmd_exe_cmd2(cmd->left);	
	}
	pid[1]= ft_fork(cmd->right);
	if (pid[1] == 0)
	{
		ft_prepare_pipe(cmd->right, NODE_RIGHT, pipefd);
		cmd_exe_cmd2(cmd->right);
	}
	// Close write end, qnd read end of the pipe
	ft_close_pipe_flows(cmd, pipefd);
	waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
	return 0;
}
