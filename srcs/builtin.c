/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:41:33 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 18:32:09 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_exit(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: exit\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_env(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: env\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_unset(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: unset\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_export(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: export\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_pwd(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: pwd\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_cd(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: cd\n");
	return (status);
}

/***********************************************************************
 * Fonction bouchon 
 * TODO: a remplacer par la vraie fonction
 ***********************************************************************/
int	cmd_echo(char **args)
{
	int	status;

	(void) args;
	status = 0;
	ft_dprintf(STDERR_FILENO, "--- builtin: echo\n");
	return (status);
}

/***********************************************************************
 * 
 * 
 * 
 ***********************************************************************/
/*
bool	is_builtin(char *cmd_str)
{
	int         i;
	const char  *builtins[] = {"echo", "cd", "pwd", "unset", "export", \
		"exit", "env", NULL};

	if (cmd_str == NULL || cmd_str[0] == '\0')
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
*/
/***********************************************************************
 * 
 * 
 * 
 ***********************************************************************/
/*
int	cmd_exe_builtin(t_cmd *cmd)
{
	char	**args;
	char	*cmd_str;
	int		status;

	status = -1;
	args = cmd->cmd_args;
	cmd_str = cmd->cmd_str;
	if (!cmd_str || !cmd_str[0])
	{
		ft_dprintf(STDERR_FILENO, "*** Error: builtin is NULL\n");
		return (status);
	}
	//TODO: manage redirections
	if (ft_strcmp("echo", cmd_str) == 0)
		status = cmd_echo(args);
	else if (ft_strcmp("unset", cmd_str) == 0)
		status = cmd_unset(args);
	else if (ft_strcmp("cd", cmd_str) == 0)
		status = cmd_cd(args);
	else if (ft_strcmp("pwd", cmd_str) == 0)
		status = cmd_pwd(args);
	else if (ft_strcmp("export", cmd_str) == 0)
		status = cmd_export(args);
	else if (ft_strcmp("env", cmd_str) == 0)
		status = cmd_env(args);
	//TODO: when do we close the file descriptors ?
	//ft_close(&cmd->file_in);
	//ft_close(&cmd->file_out);
	else if (ft_strcmp("exit", cmd_str) == 0)
	{
		//TODO: review how we process the 'exit' command
		//if (cmd->is_child == false)
		ft_dprintf(STDERR_FILENO, "--- exit \n");
		status = cmd_exit(args);
	}
	return (status);
}
*/