/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:59 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:20:35 by souaret          ###   ########.fr       */
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
/***********************************************************************
 * 
 * Execute a node in the binary tree
 * 		if operator at node level, then we call the operator execution
 *		if cmd at node level, then we execute left command first,
 *			then right command
 *		TODO: test each function
 ***********************************************************************/
int	cmd_exec_node(t_cmd *cmd)
{
	int	status;

	status = -1;
	if (!cmd)
		return (status);
	if (cmd->cmd_id == N_OPE_AND2)
		status = cmd_exe_and(cmd);
	else if (cmd->cmd_id == N_OPE_OR2)
		status = cmd_exe_or(cmd);
	else if (cmd->cmd_id == N_OPE_PIPE)
		status = cmd_exe_pipe(cmd);
	else if (cmd->cmd_id == N_CMD)
		status = cmd_exe_cmd(cmd);
	else if (cmd->cmd_id == N_CMD_BUILTIN)
		status = cmd_exe_builtin(cmd);
	else if (cmd->cmd_id == N_SUBSH)
		status = cmd_exe_subshell(cmd);
	else
		ft_printf("*** Unknown command type: %d : %s\n", \
			cmd->cmd_id, cmd->cmd_str);
	return (status);
}	

/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	cmd_exec_cmd(t_cmd *cmd, int cmd_id)
{
	(void) cmd;
	(void) cmd_id;
	status = -1;
	ft_printf("Executing command: %s\n", cmd_print(cmd_id));
	if (cmd->left || cmd->right)
	{
		ft_printf("*** Error: command is not a leaf node\n");
		return (-1);
	}
	{
		ft_printf("*** Error: command is NULL\n");
		return (-1);
	}
	status = cmd_exec_node(cmd->left);
	return (status);
}

/************************************************************************
 * 
 * Execute && command 
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
 * Execute || command (with 2 commands : LEFT || RIGHT )
 * 
 ***********************************************************************/
int	cmd_exec_or(t_cmd *cmd)
{
	int	status;

	ft_printf("--- Executing || : \n");
	if (!cmd->left || !cmd->right)
	{
		ft_printf("*** Error: operator || needs two operands\n");
		return (-1);	// error
	}
	status = cmd_exec_node(cmd->left);
	if (status == 0)
		return (0);
	status = cmd_exec_node(cmd->right);
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

	ft_printf("--- Executing subshell : \n");
	if (!cmd->left)
	{
		ft_printf("*** Error: subshell tree is NULL\n");
		return (-1);
	}
	//TODO: prepare to call subshell with a string-cmd
	//TODO: execute the subshell
	return (status);
}

/************************************************************************
 * 
 * TODO: Find a methode to execute the whole tree.
 *
*************************************************************************/
void	cmd_exec_tree(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd_exec_node(cmd);
	if (cmd->left)
		cmd_exec_tree(cmd->left);
	if (cmd->right)
		cmd_exec_tree(cmd->right);
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
	cmd_exec_tree(cmd_tree);
	//TODO: Cleanup after execution
}
