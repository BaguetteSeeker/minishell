/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:44:48 by souaret           #+#    #+#             */
/*   Updated: 2025/05/06 14:43:36 by marvin           ###   ########.fr       */
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
 *  olkd tentative 
 * 	// exit_coode = -1;
	// // --- Analyze the child's termination status ---
	// if (WIFEXITED(child_status)) {
	// 	// Child terminated normally using exit() or return
	// 	exit_code = WEXITSTATUS(child_status);
	// 	printf("Parent: Child exited normally with status code: %d\n", exit_code);
	// 	// In a real shell, you might store this value (e.g., in $?)
	// } else if (WIFSIGNALED(child_status)) {
	// 	// Child was terminated by a signal
	// 	term_signal = WTERMSIG(child_status);
	// 	printf("Parent: Child was terminated by signal: %d (%s)\n",
	// 			term_signal, strsignal(term_signal));
	// 		// In a real shell, you might report this differently, e.g. 128 + signal number
	// } else {
	// 	// Other possibilities (stopped, continued - less common for basic exec)
	// 	printf("Parent: Child terminated with unusual status: %d\n", child_status);
	// }
	// return 

*************************************************************************/
int	last_status_code(int status, bool setter)
{
	static int	code = 0;

	if (setter == true)
		code = status;
	return (code);
}

int	get_status(void)
{
	return (last_status_code(0, GET));
}

/************************************************************************
 *
 *
*************************************************************************/
int	set_status(int child_status)
{
	int	status;

	status = -1;
	if (WIFEXITED(child_status))
		status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		status = WTERMSIG(child_status);
	else if (WIFSTOPPED(child_status))
		status = WSTOPSIG(child_status);
	ft_dprintf(STDERR_FILENO, "get_status: child_status = %d\n", status);
	last_status_code(status, SET);
	return (status);
}

/************************************************************************
 *
 *
*************************************************************************/
int	ft_waitpid(int pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid error");
		free_and_exit(EXIT_FAILURE);
	}
	set_status(status);
	return (get_status());
}
/************************************************************************
 * 
 * Execute a standallone cmd
 * 
************************************************************************/
int	exec_cmd(t_cmd *cmd)
{
	int	status;

	status = -1;
	execve(cmd->cmd_str, cmd->cmd_args, NULL);
	{
		perror("execve error");
		free_and_exit(EXIT_FAILURE);
	}
	// ft_dprintf(STDERR_FILENO, "after the call to exeve\n");
	// status = get_status(ret);
	// cmd->status = -1;
	//TODO: how return status works ?
	return (status);
}

/************************************************************************
 * 
 * Execute a standallone cmd
 * 
 * old tentative:
 * 			// if (WIFEXITED(status))
			// 	status = WEXITSTATUS(status);
			// else if (WIFSIGNALED(status))
			// 	status = WTERMSIG(status);
			// else if (WIFSTOPPED(status))
			// 	status = WSTOPSIG(status);
			// else
			// 	status = -1;
************************************************************************/
int	cmd_exe_cmd2(t_cmd *cmd)
{
	int	status;
	int	pid;

	status = -99;
	if (cmd->is_child || !cmd->is_child)	// TODO: review this part
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
			ft_waitpid(pid);
			if (status == -1)
				perror("exec_cmd error");
			else
				status = get_status();
			cmd->status = status;
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
	//cmd->is_child = true;
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
	// int	status;

	pid = fork();
	do_check_error_exit((pid == -1), EXIT_FAILURE);
	if (pid == 0)
	{
		ft_dprintf(STDERR_FILENO, "Child: Executing...\n");
		cmd->is_child = true;
		//TODO: exec_cmd(cmd);
		//set_child_signals();
	}
	else
	{
        // Parent process
		cmd->pid_child = pid;
        //ft_dprintf(STDERR_FILENO, "Parent: Waiting for child <%d>\n",
		//	cmd->pid_child);
		ft_printf("Parent: Waiting for child <%d>\n", cmd->pid_child);			
    //     if (waitpid(pid, &status, 0) == -1)
    //     {
    //         perror("waitpid failed");
    //         free_and_exit(EXIT_FAILURE);
    //     }

    //     // Check if the child exited normally
    //     if (WIFEXITED(status))
	// 		ft_dprintf(STDERR_FILENO, "Child exited <%d>with status: %d\n", WIFEXITED(status), WEXITSTATUS(status));
    //     else
    //         ft_dprintf(STDERR_FILENO, "Child did not exit normally\n");
    }
	return (pid);
}
