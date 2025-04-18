/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:56:17 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:36:55 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/************************************************************************
 * 
 * 
 * TODO: review this  formula of the pipe preparation
************************************************************************/
void ft_prepare_pipe(t_cmd *cmd)
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
	if (cmd->right->file_int != STDfile_inNO)
	{
		close(cmd->right->file_in);
		cmd->right->file_in = cmd->pipe_fd[0];
	}
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
int	ft_fork_node_pipe(t_cmd node, int pos, int fd)
{
	int	pid;
	int	status;

	pid = ft_fork(node);
	do_check_error_exit((pid == -1), EXIT_FAILURE);
	if (pid == 0)
	{
		if (pos == NODE_LEFT)
		{
			ft_close(&fd[0]);
			ft_dup2(&fd[1], STDOUT_FILENO);
		}
		else
		{
			ft_close_fd(&fd[1]);
			ft_dup2(&fd[0], STDIN_FILENO);
		}
		status = exec_command(node);
		free_and_exit(status);
	}
	return (pid);
}
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
void ft_close_pipe_flows(t_cmd *cmd, int fd[2])
{
	if (cmd->left->file_out != STDOUT_FILENO)
	{
		ft_close_fd(cmd->left->file_out);
		cmd->left->out_file = STDOUT_FILENO;
	}
	if (cmd->right->file_in != STDIN_FILENO)
	{
		ft_close_fd(cmd->right->file_in);
		cmd->right->file_in = STDIN_FILENO;
	}
	ft_close_fd(fd[0]);
	ft_close_fd(fd[1]);
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
void	cmd_exec_pipe(t_cmd *cmd)
{
	int fd[2]
	int	status;

	ft_printf("Executing | : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_printf("*** Error: operator | needs two operands\n");
		return (-1);	// error
	}
	ft_prepare_pipe(cmd);
	pid0 = ft_fork_node_pipe(cmd->left, NODE_LEFT, fd);
	pid1 = ft_fork_node_pipe(cmd->right, NODE_RIGHT, fd);
	ft_close_pipe_flows(cmd, fd);
	// TODO: TO BE COMPLETED
	return ;
}
