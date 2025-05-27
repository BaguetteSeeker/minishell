/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
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

//implements the logical operators logic in the tree execution
int	execute_operator(t_ast_node *node)
{
	int	left_status;

	left_status = execute_node(node->left);
	if (node->value && ft_strcmp(node->value, "&&") == 0)
	{
		if (left_status == 0)
			return (execute_node(node->right));
		return (left_status);
	}
	else if (node->value && ft_strcmp(node->value, "||") == 0)
	{
		if (left_status != 0)
			return (execute_node(node->right));
		return (left_status);
	}
	return (1);
}

//runs subsequent branches in a new process
int	execute_subshell(t_ast_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exit(execute_node(node->left));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

//traverses the tree recursively, executes node functions when found
//finally executes command when found, and go back up in the tree
//	-if interactive and empty command, treated as a program
//	-if non-interactive, treated as an empty line
//	-if tree has var but no value, treated as a local variable declaration
//		e.g. "var1=a var2=b"
int	execute_node(t_ast_node *node)
{
	if (!node)
		return (1);
	if ((!node->value || *node->value == '\0'))
	{
		if (node->vars != NULL)
			return (assign_shell_var(node));
		if (g_getset(NULL)->mode == INTERACTIVE)
			return (ft_putendl_fd("msh: : command not found", STDERR_FILENO), 127);
		else
			return (0);
	}
	if (node->type == NODE_COMMAND)
		return (execute_command(node));
	if (node->type == NODE_OPERATOR)
		return (execute_operator(node));
	if (node->type == NODE_PIPE)
		return (execute_pipe(node));
	if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node));
	return (1);
}
