/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:44:48 by souaret           #+#    #+#             */
/*   Updated: 2025/04/22 18:57:16 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* -----------------------------------------------------------------
TODO:
	[ ] return status of child/forked process : H2 ?
	[ ] signal for forked child (SIGSTP, SIGINT, SIGQUIT)
	[ ] 

-----------------------------------------------------------------*/
/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	exec_cmd(t_cmd *cmd)
{
	int	status;
	int	pid;

	status = -1;
	pid = execve(cmd->cmd_str, cmd->cmd_args, NULL);
	if (pid == -1)
	{
		perror("execve error");
	}
	waitpid(pid, &status, 0);
	cmd->status = status;
	//TODO: how return status works ?
	return (status);
}

/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	cmd_exe_cmd2(t_cmd *cmd)
{
	int	status;
	int	pid;

	status = -1;
	if (cmd->is_child)
	{
		pid = ft_fork(cmd);
		if (pid == 0)
			status = exec_cmd(cmd);
		wait(&pid);
		if (status == -1)
		{
			perror("exec_cmd error");
		}
		return (status);
	}
	return (status);
}

/************************************************************************
 * 
 * Verify conditions to execute a standallone cmd
 * 
************************************************************************/
int	cmd_exe_cmd(t_cmd *cmd)
{
	int		status;
	char	*cmd_str;

	status = -1;
	if (!cmd)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: command is NULL\n");
		return (status);
	}
	cmd_str = cmd->cmd_str;
	if (!cmd_str)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: command is NULL\n");
		return (status);
	}
	else
		ft_dprintf(STDERR_FILENO, "Executing command: %s\n", cmd_str);
	if (cmd->left || cmd->right)
	{
		ft_dprintf(STDERR_FILENO, "*** Error: command is not a leaf node\n");
		return (status);
	}
	cmd->is_child = true;
	status = cmd_exe_cmd2(cmd);
	return (status);
}
