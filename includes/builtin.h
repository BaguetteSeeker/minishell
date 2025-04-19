/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:33:10 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 16:40:26 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int		cmd_echo(char **args);
int		cmd_cd(char **args);
int		cmd_pwd(char **args);
int		cmd_export(char **args);
int		cmd_unset(char **args);
int		cmd_env(char **args);
int		cmd_exit(char **args);
bool	is_builtin(char *cmd_str);
int		cmd_exe_builtin(t_cmd *cmd);
//int		exec_builtin(t_cmd *cmd);

#endif