/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:10:10 by souaret           #+#    #+#             */
/*   Updated: 2025/01/27 19:56:13 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------------------------------------------------------------------
 *
  Utilities functions to manage cmd trees
    these are CRUD operations (basic operations that we would need)

    TODO: This is work in progress 
	- create define ERR_CMD_0	// no nodes created !
	- create define ERR_CMD_1	// cmd_tree & cmd cannot be the identical
								// canot be NULL or ! NULL alltogether
	- create define ERR_CMD_2	
	- create define ERR_CMD_3	// cannot add null child 
	- create define ERR_CMD_4	// cannot add child (no left or right)
	- create define ERR_CMD_5	// about to overright a child
	- create define ERR_CMD_6	// cannot find root node (null)

 * TODO: 
 * 		create enum : t_child
 * 		- T_LEFT
 * 		- T_RIGHT
 -----------------------------------------------------------------------*/
/*************************************************************************
 * getter for cmd
*************************************************************************/
t_cmd	*cmd_get(t_cmd *cmd)
{
	static t_cmd	*cmd_tree = NULL;

	if (cmd_tree != NULL && cmd == NULL)
		return (cmd_tree);
	else if (cmd_tree == NULL && cmd != NULL)
		cmd_tree = cmd;
	else 
		do_error_exit(ERR_CMD_1);
	return (NULL);
}

/************************************************************************
 * getter for cmd
*************************************************************************/
void	cmd_set(t_cmd *cmd)
{
	cmd_get(cmd);
}

/*************************************************************************
 * 
 * Create node for a cmd - unfinished work
*************************************************************************/
t_cmd	*cmd_create(int cmd_id, char *str)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	do_check_error_exit((new_cmd == NULL), ERR_CMD_1);
	new_cmd->cmd_id = cmd_id;
	new_cmd->cmd_str = ft_strdup(str);
	do_check_error_exit((new_cmd->cmd_str == NULL), ERR_CMD_2);
	new_cmd->cmd_args = NULL;
	new_cmd->left = NULL;
	new_cmd->right = NULL;
	new_cmd->parent = NULL;
	return (new_cmd);
}

/************************************************************************
 *  Add child node to a cmd
*************************************************************************/
void	cmd_add_child(t_cmd *node, t_cmd *child, int child_node)
{
	t_cmd	*temp;

	temp = NULL;
	if (child == NULL)
		do_error_exit(ERR_CMD_3);
	if (child_node == T_LEFT)
		temp = node->left;
	else if (child_node == T_RIGHT)
		temp = node->right;
	else
		do_error_exit(ERR_CMD_4);
	if (temp)
		temp = child;
	else
		do_error_exit(ERR_CMD_5);
}

/************************************************************************
 * delete a node and its constituents
*************************************************************************/
void	cmd_delete(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd_delete(cmd->left);
	cmd->left = NULL;
	cmd_delete(cmd->right);
	cmd->right = NULL;
	free_str(&cmd->cmd_str);
	cmd->cmd_str = NULL;
	free_str(cmd->cmd_args);
	cmd->cmd_args = NULL;
	free(cmd);
}
