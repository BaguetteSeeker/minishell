/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:44:48 by souaret           #+#    #+#             */
/*   Updated: 2025/04/25 16:37:16 by souaret          ###   ########.fr       */
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
 *
 * 
*************************************************************************/
int	get_status(int pid)
{
	int	status;

	status = -1;
	if (pid == -1)
	{
		perror("get_status error");
		return (-1);
	}
	if (WIFEXITED(pid))
		status = WEXITSTATUS(pid);
	else if (WIFSIGNALED(pid))
		status = WTERMSIG(pid);
	else if (WIFSTOPPED(pid))
		status = WSTOPSIG(pid);
	return (status);
}

/************************************************************************
 *
 *
 * 
*************************************************************************/
int	ft_waitpid(int pid, int *status, int options)
{
	int ret;

	ret = waitpid(pid, status, options);
	if (ret == -1)
	{
		perror("waitpid error");
		free_and_exit(EXIT_FAILURE);
	}
	// if (waitpid(pid, status, 0) == -1)
	// {
	// 	perror("waitpid failed");
	// 	exit(EXIT_FAILURE);
	// }

	// Check if the child exited normally
	if (WIFEXITED(*status))
	{
		printf("Child exited with status: %d\n", WEXITSTATUS(*status));
	}
	else
	{
		printf("Child did not exit normally\n");
	}
	return (ret);
}
/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	exec_cmd(t_cmd *cmd)
{
	int	status;
	int	ret;

	status = -1;
	ret = execve(cmd->cmd_str, cmd->cmd_args, NULL);
	if (ret == -1)
	{
		perror("execve error");
	}
	status = get_status(ret);
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
		{
			status = exec_cmd(cmd);
			free_and_exit(EXIT_SUCCESS);	// TODO:: review real status here 
		}
		else
		{
			// TODO: redo this part ...!
			ft_waitpid(pid, &status, 0);
			if (status == -1)
				perror("exec_cmd error");
			else
				status = get_status(pid);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status);
			else if (WIFSTOPPED(status))
				status = WSTOPSIG(status);
			else
				status = -1;
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


/************************************************************************
 *
 * //cmd->pid = getpid();
 * 
*************************************************************************/
int	ft_fork(t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	do_check_error_exit((pid == -1), EXIT_FAILURE);
	if (pid == 0)
	{
		ft_dprintf(STDERR_FILENO, "Child process: Executing...\n");
		cmd->is_child = true;
		cmd->pid = pid;
		//TODO: exec_cmd(cmd);
		//set_child_signals();
	}
	else
	{
        // Parent process
        ft_dprintf(STDERR_FILENO, "Parent process: Waiting for child to finish...\n");
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
            free_and_exit(EXIT_FAILURE);
        }

        // Check if the child exited normally
        if (WIFEXITED(status))
			ft_dprintf(STDERR_FILENO, "Child exited with status: %d\n", WEXITSTATUS(status));
        else
            ft_dprintf(STDERR_FILENO, "Child did not exit normally\n");
    }
	return (pid);
}
