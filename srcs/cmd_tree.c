/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:15:25 by souaret           #+#    #+#             */
/*   Updated: 2025/05/06 15:00:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**---------------------------------------------------------------------------
 * WARNING: This is a simulation functions to create AST structures
 *			- it is not to be used in the final version
-----------------------------------------------------------------------------*/
/*****************************************************************************
 * 
 * 
******************************************************************************/
t_cmd	*node_add_top(t_cmd *root, t_cmd *new_node)
{
	if (!new_node)
		return (root);
	new_node->left = root;
	return (new_node);
}

/*
t_cmd	*node_add_bottom(t_cmd *root, t_cmd *new_node)
{
	t_cmd	*current;

	if (!root)
		return (new_node);
	current = root;
	while (current->left)
		current = current->left;
	current->left = new_node;
	return (root);
}
*/
/*****************************************************************************
 * 
 * 
******************************************************************************/
t_cmd	*node_add_left(t_cmd *parent, t_cmd *new_node)
{
	if (!parent || !new_node)
		return (NULL);
	parent->left = new_node;
	return (parent);
}

/*****************************************************************************
 * 
 * 
******************************************************************************/
t_cmd	*node_add_right(t_cmd *parent, t_cmd *new_node)
{
	if (!parent || !new_node)
		return (NULL);
	parent->right = new_node;
	return (parent);
}

void	node_free(t_cmd *node)
{
	if (!node)
		return ;
	node_free(node->left);
	node_free(node->right);
	free_str((char **)&node);
}

/*****************************************************************************
 * 
 * 
******************************************************************************/
t_cmd	*node_new(char *cmd_str)
{
	t_cmd	*new_node;

	if (!cmd_str)
		return (NULL);
	new_node = malloc(sizeof(t_cmd));
	do_check_error_exit(!new_node, ERR_MALLOC);
	new_node->cmd_str = ft_strdup(cmd_str);
	if (is_builtin(cmd_str))
	{
		new_node->cmd_id = get_builtin_id(cmd_str);
		new_node->node_type = N_CMD_BUILTIN;
	}	
	else
	{
		new_node->cmd_id = CMD_EXT;
		new_node->node_type = N_CMD;
	}
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->cmd_args = NULL;
	new_node->file_in = -1;
	new_node->file_out = -1;
	return (new_node);
}
/*
	//new_node->cmd_id = id;
	//	new_node->cmd_str = ft_strdup(cmd_str);
	// new_node->heredoc = NULL;
	// new_node->type = -1;
	// new_node->is_builtin = false;
	// new_node->is_pipe = false;
	// new_node->is_redir = false;
	// new_node->is_heredoc = false;
	// new_node->is_cmd = false;
	// new_node->is_cmd_args = false;
	// new_node->is_cmd_name = false;
	// new_node->is_cmd_redir = false;
	// new_node->is_cmd_heredoc = false;
	// new_node->is_cmd_pipe = false;
	// new_node->is_cmd_builtin = false;
*/
