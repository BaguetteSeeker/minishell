/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:28:16 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 16:23:29 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

//void	exec_cmd(void);
int		cmd_exe_node(t_cmd *cmd);
int		cmd_exe_cmd(t_cmd *cmd);
int		cmd_exe_and(t_cmd *cmd);
int		cmd_exe_or(t_cmd *cmd);
int		cmd_exe_subshell(t_cmd *cmd);
void	cmd_exe_tree(t_cmd *cmd);
void	cmd_exec(void);

#endif