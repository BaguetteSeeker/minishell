/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:59 by souaret           #+#    #+#             */
/*   Updated: 2025/01/26 21:13:08 by souaret          ###   ########.fr       */
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
		- Initialize status
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
	return ;
}

/************************************************************************
 * 
 * 
 * 
************************************************************************/
void	cmd_exec_ope(t_cmd *cmd, int node_type)
{
	(void)cmd;
	(void) node_type;
	// TODO: implemented later 
	return ;
}

/************************************************************************
 * 
 * Execute a node in the binary tree
 * 		if operator at node level, then we call the operator execution
*		if cmd at node level, then we execute left command first,
*			then right command	
 * TODO: Stopped here : what strategy to store AST
************************************************************************/
void	cmd_exec_node(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->node_type == T_OPE)
	{
		cmd_exec_ope(cmd, cmd->node_type);
	}
	else if (cmd->node_type == T_CMD)
	{
		cmd_exec_cmd(cmd, cmd->cmd_id);
	}
	if (cmd->left)
		cmd_exec_node(cmd->left);
}

/************************************************************************
 * 
 * Main entry point for executing a command in the minishell
 * TODO: WIP    -  Work in progress
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
