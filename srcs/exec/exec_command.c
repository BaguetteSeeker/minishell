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
	char	**argv;
	char	**envp;
	int		redir_status;
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	redir_status = redirections_handler(node);
	if (redir_status !=0)
		return (clean_shell(), exit(redir_status));
	envp = g_getset(NULL)->var_env;
	path = get_cmdpath(node->value, envp);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "msh: %s: Command not found\n", 
			node->value), clean_shell(), exit(EXITC_NOCMD));
	argv = get_cmdargv(node->value, node->args);
	if (!argv)
		return (perror(node->value), clean_shell(), free(path), exit(1));
	update_add_var(VAR_ENV, "_", node->value);
	envp = g_getset(NULL)->var_env;
	printf("%s\n", node->value);
	fflush(stdout);
	execve(path, argv, envp);
	perror("execve failed");
	free_tab((void **)argv);
	clean_shell();
	exit(1);
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
	t_bi_type type = is_builtin(node->value);

	printf("foreground : %d\n", node->is_foreground);
	if (node->is_foreground == 1)
		update_underscore(node);
	expand_node(node);
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
	return (exit_status);
}
