/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:59 by souaret           #+#    #+#             */
/*   Updated: 2025/04/15 16:45:10 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------------------------------------------------------------------
 * This is the execution part of the minishell
 *		- it will execute the commands as organized in the binary tree. 
 *        It will manage the following:
 *		- pipes
 *		- redirections
 *		- environment variables
 *		- exit status
 *		- signals
 *		- output of the command
 *      - results of the cmd ( status )
 *      - error handling
 *      - cleanup after execution & house keeping
 * 
 * Workflow of operations :
 *		- Initialize environemnt variables
 *		- Initialize input / output environments
 *		- Initialize heredoc
 *		- Initialize status
 * 
 * Execution cycle:
 *		- Executes the cmd tree in a left-node-right order, recursively
------------------------------------------------------------------------*/
/************************************************************************
 * 
 * 
 * 
************************************************************************/
void	cmd_exec_cmd(t_cmd *cmd, int cmd_id)
{
	(void)cmd;
	(void) cmd_id;
	printf("Executing command: %s\n", cmd_print(cmd_id));
	//TODO: 
	return ;
}

/************************************************************************
 * 
 * Execute a && command 
 * a command that executes well, returns OK.
 * 	if status of LEFT cmd is not OK ( = 0), 
 * 		then no need to execute the RIGHT cmd
************************************************************************/
int	cmd_exec_and(t_cmd *cmd)
{
	int	status;

	printf("--- Executing && : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_printf("*** Error: && operator needs two operands\n");
		return (-1);	// error
	}
	status = cmd_exec_node(cmd->left);
	if (status != 0)
		return (-1);
	status = cmd_exec_node(cmd->right);
	return (status);
}

/************************************************************************
 * 
 * Execute || command (with 2 commands : LEFT and RIGHT
 * 
 * TODO: if an error occured, exit with the error code, 
 * 		 freeall, clean-up and exit.
************************************************************************/
int	cmd_exec_or(t_cmd *cmd)
{
	int	status;

	ft_printf("--- Executing || : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_printf("*** Error: || operator needs two operands\n");
		return (-1);	// error
	}
	status = cmd_exec_node(cmd->left);
	if (status == 0)
		return (0);
	status = cmd_exec_node(cmd->right);
	return (status);
}

/************************************************************************
 * 
 * 
 * TODO: review this copiplot formula of the pipe preparation
************************************************************************/
void ft_prepare_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (cmd->left->out_file != STDOUT_FILENO)
	{
		close(cmd->left->out_file);
		cmd->left->out_file = cmd->pipe_fd[1];
	}
	if (cmd->right->in_file != STDIN_FILENO)
	{
		close(cmd->right->in_file);
		cmd->right->in_file = cmd->pipe_fd[0];
	}
}

/************************************************************************
 * 
 * 
 * 
************************************************************************/
void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDERR_FILENO
		|| *fd == STDOUT_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		perror("close");
		free_and_exit(1);
	}
	*fd = -1;
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
			ft_close(&fd[1]);
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
	if (cmd->left->out_file != STDOUT_FILENO)
	{
		ft_close(cmd->left->out_file);
		cmd->left->out_file = STDOUT_FILENO;
	}
	if (cmd->right->in_file != STDIN_FILENO)
	{
		ft_close(cmd->right->in_file);
		cmd->right->in_file = STDIN_FILENO;
	}
	ft_close(fd[0]);
	ft_close(fd[1]);
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
		ft_printf("*** Error: | operator needs two operands\n");
		return (-1);	// error
	}
	ft_prepare_pipe(cmd);
	pid0 = ft_fork_node_pipe(cmd->left, NODE_LEFT, fd);
	pid1 = ft_fork_node_pipe(cmd->right, NODE_RIGHT, fd);
	ft_close_pipe_flows(cmd, fd);
	// TODO: TO BE COMPLETED
	return ;
}

/***********************************************************************
 * 
 * Execute a node in the binary tree
 * 		if operator at node level, then we call the operator execution
 *		if cmd at node level, then we execute left command first,
 *			then right command	
 ***********************************************************************/
void	cmd_exec_node(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd_id == N_OPE_AND2)
		cmd_exe_and(cmd);
	else if (cmd->cmd_id == N_OPE_OR2)
		cmd_exe_or(cmd);
	else if (cmd->cmd_id == N_OPE_PIPE)
		cmd_exe_pipe(cmd);
	else if (cmd->cmd_id == N_SUBsh)
		cmd_exe_subshell(cmd);
	else if (cmd->cmd_id == N_CMD)
		cmd_exe_cmd(cmd);
	else
		ft_printf("*** Unknown command type: %d\n", cmd->cmd_id);
	return ;
}	

/************************************************************************
 * 
 * Main entry point for executing a command in the minishell
 * it will execute the command tree
 *
*************************************************************************/
void	cmd_exec(void)
{
	t_cmd	*cmd_tree;

	//TODO: Prepare for execution
	cmd_tree = cmd_get(NULL);
	do_check_error_exit((cmd_tree == NULL), ERR_2);
	cmd_exec_node(cmd_tree);
	//TODO: Cleanup after execution
}
