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

//debug function
void	print_tab(char **t)
{
	int	i;

	i = 0;
	printf("argv :\n");
	if (!t)
		printf("(null)\n");
	while (t[i])
	{
		printf("%d : %s \n", i, t[i]);
		i++;
	}
}
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
	int		redirs;

	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	redirs = redirections_handler(node);
	if (redirs !=0)
		return (clean_shell(), exit(redirs), exit(1));
	envp = g_getset(NULL)->var_env;
	path = get_cmdpath(node->value, envp);
	if (!path)
		return (perror(node->value), clean_shell(), exit(EXITC_NOCMD));
	if (access(path, F_OK | X_OK) != 0)
		return (perror(node->value), clean_shell(), exit(EXITC_NOEXEC));
	argv = get_cmdargv(node->value, node->args);
	if (!argv)
		return (perror(node->value), clean_shell(), free(path), exit(1));
	execve(path, argv, envp);
	perror("execve failed");
	free(path);
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
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_fork(node);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
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
int	execute_node(t_ast_node *node)
{
	if (!node)
		return (1);
	if (!node->value || *node->value == '\0')
		return (0);
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
