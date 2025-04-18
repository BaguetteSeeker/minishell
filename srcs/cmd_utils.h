/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:48:47 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:37:54 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_UTILS_H
# define CMD_UTILS_H

typedef enum e_node_dir
{
	T_LEFT,
	T_RIGHT
}	t_node_dir;

# define CMD_ECHO	1
# define CMD_PWD	2
# define CMD_CD		3
# define CMD_EXPORT	4
# define CMD_UNSET	5
# define CMD_ENV	6
# define CMD_EXIT	7

t_cmd	*cmd_get(t_cmd *cmd);
void	cmd_set(t_cmd *cmd);
t_cmd	*cmd_create(int cmd_id, char *str);
void	cmd_add_child(t_cmd *node, t_cmd *child, int child_node);
void	cmd_delete(t_cmd *cmd);
void	cmd_free_all(void);
char	*cmd_print(int cmd_id);

#endif