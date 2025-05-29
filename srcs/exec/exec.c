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

//set foreground flag off recursively in all node below passed node
void	set_foreground_flag(t_ast_node *node)
{
	if (!node)
		return;
	node->is_foreground = 0;
	set_foreground_flag(node->left);
	set_foreground_flag(node->right);
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

	set_foreground_flag(node);
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
	node->is_foreground = 1;
	if (!node)
		return (1);
	if ((!node->args[0] || *node->args[0] == '\0'))
	{
		if (node->vars != NULL)
			return (assign_shell_var(node));
		if (g_getset(NULL)->mode == INTERACTIVE)
			return (ft_putendl_fd("msh: (null) : command not found", STDERR_FILENO), 127);
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
