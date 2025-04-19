/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:49:23 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 17:15:15 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CMDS_H
# define STRUCT_CMDS_H

/**************************************************************************
 * Type of node : 
 * 	N_CMD		: command or explicitely distinguished commands: 
 * 	   N_CMDint	:    internal command (built-in)
 * 	   N_CMDext	:    external command
 * 	N_OPE_AND2	: operator : logical AND
 * 	N_OPE_OR2	: operator : logical OR
 * 	N_OPE_PIPE	: operator : pipe
 * 	N_SUBsh		: sub-shell
**************************************************************************/
typedef enum e_node_type
{
	N_CMD,
	N_OPE_AND2,
	N_OPE_OR2,
	N_OPE_PIPE,
	N_SUBSH,
	N_CMD_BUILTIN
}	t_node_type;

/**************************************************************************
 * Build-ins commands :
 * Command ID: to identify the command
 *		CMD_EXT		: external command
 *		CMD_ECHO	: echo
 *		CMD_CD		: cd
 *		CMD_PWD		: pwd
 *		CMD_EXPORT	: export
 *		CMD_UNSET	: unset
 *		CMD_ENV		: env
 *		CMD_EXIT	: exit
**************************************************************************/
typedef enum e_cmd_bi
{
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT
}	t_cmd_bi;

# define NODE_LEFT	1
# define NODE_RIGHT	2

/**************************************************************************
 * 
 * Structure to store parser elements processed and identified
 *		node_type	: enum t_node_type
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
	t_cmd_bi		cmd_id;
	char			*cmd_str;
	char			**cmd_args;
	struct s_cmd	*left;
	struct s_cmd	*right;
	//struct s_cmd	*parent;
	bool			is_child;
	int				file_in;
	int				file_out;
	bool			file_append;
	int				pipe_fd[2];
	int				status;
	int				pid;
}					t_cmd;

#endif