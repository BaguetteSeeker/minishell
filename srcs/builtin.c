/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:41:33 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:17:36 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <stdbool.h>
// #include <stddef.h> // For NULL

/***********************************************************************
 * 
 * 
 * 
 ***********************************************************************/
bool	is_builtin(char *cmd_str)
{
	int         i;
	const char  *builtins[] = {"echo", "cd", "pwd", "unset", "export", \
		"exit", "env", NULL};

	if (cmd_str == NULL || cmd_str[0] == NULL)
		return (false);
    i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd_str) == 0)
			return (true);
		i++;
	}
	return (false);
}

/***********************************************************************
 * 
 * 
 * 
 ***********************************************************************/
int	exec_builtin(t_cmd *cmd)
{
	char	**args;
	int		status;

	status = -1;
	args = cmd->str;
	if (ft_strcmp("echo", args[0]) == 0)
		status = cmd_echo(args);
	else if (ft_strcmp("unset", args[0]) == 0)
		status = cmd_unset(args);
	else if (ft_strcmp("cd", args[0]) == 0)
		status = cmd_cd(args);
	else if (ft_strcmp("pwd", args[0]) == 0)
		status = cmd_pwd(args);
	else if (ft_strcmp("export", args[0]) == 0)
		status = cmd_export(args);
	else if (ft_strcmp("env", args[0]) == 0)
		status = cmd_env(args);
	//TODO: when do we close the file descriptors ?
	//ft_close(&cmd->file_in);
	//ft_close(&cmd->file_out);
	else if (ft_strcmp("exit", args[0]) == 0)
	{
		if (cmde->is_child == false)
			ft_putendl_fd("exit", STDERR_FILENO);
		status = ft_exit(args);
	}
	return (status);
}
