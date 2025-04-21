/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:59 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 18:38:56 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------------------------------------------------------------------
 * This is the execution part of the minishell
 *		- it will execute the commands as organized in the binary tree. 
 *
 *   It will/should manage the following:
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
 *
 * TODO: if an error occurs on any node, what to do ?
 * 			exit with the error code ?
 * 		 	free-all ?
 * 			close all ? 
 * 			clean-up ?
 * 			exit ?
*
------------------------------------------------------------------------*/
/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	cmd_exe_cmd(t_cmd *cmd)
{
	int		status;
	char	*cmd_str;

	status = -1;
	if (!cmd)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: command is NULL\n");
		return (status);
	}
	cmd_str = cmd->cmd_str;
	ft_dprintf(STDERR_FILENO, "Executing command: %s\n", cmd_str);
	if (cmd->left || cmd->right)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: command is not a leaf node\n");
		return (-1);
	}
	status = cmd_exe_node(cmd->left);
	return (status);
}

/************************************************************************
 * 
 * Execute && command 
 * a command that executes well, returns OK.
 * 	if status of LEFT cmd is not OK ( = 0), 
 * 		then no need to execute the RIGHT cmd
************************************************************************/
int	cmd_exe_and(t_cmd *cmd)
{
	int	status;

	ft_dprintf(STDERR_FILENO, "--- Executing && : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: &&  needs two operands\n");
		return (-1);
	}
	status = cmd_exe_node(cmd->left);
	if (status != 0)
		return (-1);
	status = cmd_exe_node(cmd->right);
	return (status);
}

/************************************************************************
 * 
 * Execute || command (with 2 commands : LEFT || RIGHT )
 * 
 ***********************************************************************/
int	cmd_exe_or(t_cmd *cmd)
{
	int	status;

	ft_dprintf(STDERR_FILENO, "--- Executing || : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: || needs two operands\n");
		return (-1);
	}
	status = cmd_exe_node(cmd->left);
	if (status == 0)
		return (0);
	status = cmd_exe_node(cmd->right);
	return (status);
}

/***********************************************************************
 * 
 * Execute a node in the binary tree
 * 		if operator at node level, then we call the operator execution
 *		if cmd at node level, then we execute left command first,
 *			then right command	
 ***********************************************************************/
int	cmd_exe_subshell(t_cmd *cmd)
{
	int	status;

	status = -1;
	ft_dprintf(STDERR_FILENO, "--- Executing subshell : \n");
	if (!cmd->left)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: subshell tree is NULL\n");
		return (-1);
	}
	//TODO: prepare to call subshell with a string-cmd
	//TODO: execute the subshell
	return (status);
}

/***********************************************************************
 * 
 * Execute a node in the binary tree
 * 		if operator at node level, then we call the operator execution
 *		if cmd at node level, then we execute left command first,
 *			then right command
 *		TODO: test each function
 ***********************************************************************/
int	cmd_exe_node(t_cmd *cmd)
{
	int	status;

	status = -1;
	if (!cmd)
		return (status);
	if (cmd->node_type == N_CMD)
		status = cmd_exe_cmd(cmd);
	else if (cmd->node_type == N_CMD_BUILTIN)
		status = cmd_exe_builtin(cmd);
	else if (cmd->node_type == N_SUBSH)
		status = cmd_exe_subshell(cmd);
	else if (cmd->node_type == N_OPE_AND2)
		status = cmd_exe_and(cmd);
	else if (cmd->node_type == N_OPE_OR2)
		status = cmd_exe_or(cmd);
	else if (cmd->node_type == N_OPE_PIPE)
		status = cmd_exe_pipe(cmd);
	else
		ft_dprintf(STDERR_FILENO, "*** Unknown command type: %d : %s\n", \
			cmd->node_type, cmd->cmd_str);
	return (status);
}

/************************************************************************
 * 
 * Main entry point for executing a command in the minishell
 * it will execute the command tree
 *
*************************************************************************/
void	cmd_exec(void)
{
	t_cmd	*cmd;

	//TODO: Prepare for execution
	cmd = cmd_get(NULL);
	do_check_error_exit((cmd == NULL), ERR_0);
	// cmd_exe_tree(cmd_tree);
	cmd_exe_node(cmd);
	if (cmd->left)
		cmd_exe_node(cmd->left);
	if (cmd->right)
		cmd_exe_node(cmd->right);
	//TODO: Cleanup after execution
	return ;
}
