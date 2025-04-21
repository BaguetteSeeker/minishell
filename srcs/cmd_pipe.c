/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:56:17 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 18:33:45 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************************
 * 
 * 
 * TODO: review this  formula of the pipe preparation
************************************************************************/
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
			ft_close_fd(&fd[0]);
			ft_dup2(&fd[1], STDOUT_FILENO);
		}
		else
		{
			ft_close_fd(&fd[1]);
			ft_dup2(&fd[0], STDIN_FILENO);
		}
		status = cmd_exe_node(node);
		free_and_exit(status);
	}
	return (pid);
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
void	ft_close_pipe_flows(t_cmd *cmd, int fd[2])
{
	if (cmd->left && cmd->left->file_out != STDOUT_FILENO)
	{
		ft_close_fd(&cmd->left->file_out);
		cmd->left->file_out = STDOUT_FILENO;
	}
	if (cmd->right && cmd->right->file_in != STDIN_FILENO)
	{
		ft_close_fd(&cmd->right->file_in);
		cmd->right->file_in = STDIN_FILENO;
	}
	ft_close_fd(&fd[0]);
	ft_close_fd(&fd[1]);
}

/************************************************************************
 * 
 * 
 * TODO: Review this code & test behavior
************************************************************************/
int	cmd_exe_pipe(t_cmd *cmd)
{
	int	status;
	int	fd[2];
	int	pid[2];

	status = -1;
	ft_printf("Executing | : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_printf("*** Error: operator | needs two operands\n");
		return (-1); // error
	}
	ft_prepare_pipe(cmd);
	pid[0] = ft_fork_node_pipe(cmd->left, NODE_LEFT, fd);
	pid[1] = ft_fork_node_pipe(cmd->right, NODE_RIGHT, fd);
	ft_close_pipe_flows(cmd, fd);
	// TODO: TO BE COMPLETED
	return (status);
}
