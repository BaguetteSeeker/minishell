/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:22:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/18 18:22:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//routine called inside the fork
//if redirection failed, exit with adequate exit code
//if command not found, exit with 127
//if command can't be executed, exit with 126
//if failed to create argv, exit with 1
void	exec_fork(t_ast_node *node)
{
	char	*path;
	char	**envp;
	int		redir_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	redir_status = redirections_handler(node);
	if (redir_status !=0)
		return (clean_shell(), exit(redir_status));
	envp = g_getset(NULL)->var_env;
	path = get_cmdpath(node->exp_args[0], envp);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "yes msh: %s: Command not found\n", 
			node->exp_args[0]), clean_shell(), exit(EXITC_NOCMD));
	update_add_var(VAR_ENV, "_", node->exp_args[0]);
	envp = g_getset(NULL)->var_env;
	execve(path, node->exp_args, envp);
	perror("execve failed");
	clean_shell();
	exit(1);
}

void	set_exitcode(int exitcode)
{
	g_getset(NULL)->last_exitcode = exitcode;
	update_var_exitcode();
}

//forks and calls the execution routine
//waits for process to exit
//catches exit signal if any
//returns adequate exit code
int	execute_command(t_ast_node *node)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	t_bi_type type;

	exit_status = expand_node(node);
	if (exit_status)
		return (set_exitcode(2), 2);
	// print_tab(node->exp_args);
	// if (node->io_streams)
	// 	printf("\n old %s new %s", node->io_streams->file, node->io_streams->exp_file);
	//fflush(stdout);
	if (!node->exp_args[0])
		return (set_exitcode(0), 0);
	type = is_builtin(node->exp_args[0]);
	if (type != -1)
		return(run_builtin(type, node));
	pid = fork();
	if (pid == 0)
		exec_fork(node);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = WEXITSTATUS(status);
	if (node->is_foreground == 1)
		update_underscore(node);
	return (set_exitcode(exit_status), exit_status);
}
