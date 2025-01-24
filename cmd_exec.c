/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:15:59 by souaret           #+#    #+#             */
/*   Updated: 2025/01/24 21:13:17 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------------------------------------------------------------------
 * This is the execution part of the minishell
 *		- it will execute the commands in the tree, and manage the:
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
 * Main entry point for executing a command in the minishell
 * TODO: WIP    -  Work in progress
*************************************************************************/
void	exec_cmd(void)
{
	t_cmd	*cmd_tree;

	cmd_tree = cmd_get(NULL);
	do_check_error_exit((cmd_tree == NULL), ERR_2);
	while (cmd_tree)
	{
		if (cmd_tree->left)
		{
			cmd_exec(cmd_tree->left);
		}
		temp = temp->child_right;
	}
}
