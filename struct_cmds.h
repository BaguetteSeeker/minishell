/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:49:23 by souaret           #+#    #+#             */
/*   Updated: 2025/01/25 16:36:48 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CMDS_H
# define STRUCT_CMDS_H

typedef enum e_node_type
{
	T_CMD,
	T_OPE
}	t_node_type;

/**************************************************************************
 * 
 * Structure to store parser elements processed and identified
 *		node_type	: T_CMD or T_OPE
 *		cmd_id		: id of the command, 0 if command is external
 *		cmd_str		: string of the command (if we need the exact syntax)
 *		cmd_args	: array of the command, as passed in the cmd line
 * 		left		: pointer to the left child
 * 		right		: pointer to the right child
 * 		parent		: pointer to the parent node
 * 
**************************************************************************/
typedef struct s_cmd
{
	t_node_type		node_type;
	int				cmd_id;
	char			*cmd_str;
	char			**cmd_args;
	struct s_cmd	*left;
	struct s_cmd	*right;
	struct s_cmd	*parent;
}					t_cmd;

#endif