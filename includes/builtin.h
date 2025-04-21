/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:33:10 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 17:41:44 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

// Define a function pointer type for built-in commands
typedef int	(*builtin_func)(char **args);

// Structure to associate a keyword with its function
typedef struct s_builtin
{
	const char		*keyword;
	int				cmd_bi_id;
	builtin_func	func;
}	t_builtin;

# define CMD_ERROR	-1
# define CMD_EXT	0
# define CMD_ECHO	1
# define CMD_PWD	2
# define CMD_CD		3
# define CMD_EXPORT	4
# define CMD_UNSET	5
# define CMD_ENV	6
# define CMD_EXIT	7

t_builtin	*builtin_init(void);
t_builtin	*builtin_get(char *cmd_str);
int			get_builtin_id(char *cmd_str);
int			cmd_echo(char **args);
int			cmd_cd(char **args);
int			cmd_pwd(char **args);
int			cmd_export(char **args);
int			cmd_unset(char **args);
int			cmd_env(char **args);
int			cmd_exit(char **args);
bool		is_builtin(char *cmd_str);
int			cmd_exe_builtin(t_cmd *cmd);

#endif