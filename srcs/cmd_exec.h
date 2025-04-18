/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:28:16 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:20:29 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

void	exec_cmd(void);
int		cmd_exec_node(t_cmd *cmd);
int		cmd_exec_cmd(t_cmd *cmd, int cmd_id);
int		cmd_exec_and(t_cmd *cmd);
int		cmd_exec_or(t_cmd *cmd);
int		cmd_exe_subshell(t_cmd *cmd);
void	cmd_exec_tree(t_cmd *cmd);
void	cmd_exec(void);

#endif