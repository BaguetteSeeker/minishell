/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
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
	path = get_cmdpath(node->new_args[0], envp);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "msh: %s: Command not found\n", 
			node->new_args[0]), clean_shell(), exit(EXITC_NOCMD));
	update_add_var(VAR_ENV, "_", node->new_args[0]);
	envp = g_getset(NULL)->var_env;
	fflush(stdout);
	execve(path, node->new_args, envp);
	perror("execve failed");
	clean_shell();
	exit(1);
}

int	exec_builtins(t_ast_node *node, t_bi_type type)
{
	int	exit_status;

	exit_status = run_builtin(type, node);
	g_getset(NULL)->last_exitcode = exit_status;
	update_var_exitcode();
	return (exit_status);
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

	expand_node(node);
	type = is_builtin(node->new_args[0]);
	if (type != -1)
		return(exec_builtins(node, type));
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
	g_getset(NULL)->last_exitcode = exit_status;
	update_var_exitcode();
	return (exit_status);
}
