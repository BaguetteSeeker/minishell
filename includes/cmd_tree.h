/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:34:43 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 17:43:47 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TREE_H
# define CMD_TREE_H

t_cmd	*node_add_top(t_cmd *root, t_cmd *new_node);
t_cmd	*node_add_bottom(t_cmd *root, t_cmd *new_node);
t_cmd	*node_add_left(t_cmd *parent, t_cmd *new_node);
t_cmd	*node_add_right(t_cmd *parent, t_cmd *new_node);
void	node_free(t_cmd *node);
t_cmd	*node_new(char *cmd_str);

#endif