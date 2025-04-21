/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:48:47 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 17:31:44 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_UTILS_H
# define CMD_UTILS_H

typedef enum e_node_dir
{
	T_LEFT,
	T_RIGHT
}	t_node_dir;

/*
# define CMD_ECHO	1
# define CMD_PWD	2
# define CMD_CD		3
# define CMD_EXPORT	4
# define CMD_UNSET	5
# define CMD_ENV	6
# define CMD_EXIT	7
*/

/*************************************************************************
 * 
 * 
 // # define ERR_CMD_0	// no nodes created !
 // # define ERR_CMD_1	// cmd_tree & cmd cannot be the identical
 // 							// canot be NULL or ! NULL alltogether
 // # define ERR_CMD_2	
 // # define ERR_CMD_3	// cannot add null child 
 // # define ERR_CMD_4	// cannot add child (no left or right)
 // # define ERR_CMD_5	// about to overright a child
 // # define ERR_CMD_6	// cannot find root node (null)
 * 
 ************************************************************************/

# define ERR_CMD_0	0
# define ERR_CMD_1	1
# define ERR_CMD_2	2
# define ERR_CMD_3	3
# define ERR_CMD_4	4
# define ERR_CMD_5	5
# define ERR_CMD_6	6

void		cmd_set(t_cmd *cmd);
t_cmd		*cmd_get(t_cmd *cmd);
t_cmd		*cmd_create(int cmd_id, char *str);
void		cmd_add_child(t_cmd *node, t_cmd *child, int child_node);
void		cmd_delete(t_cmd *cmd);
void		cmd_free_all(void);
const char	*cmd_print(int cmd_id);

#endif