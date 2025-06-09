/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//resors stdio file descriptors in parent process
void restore_stdio_builtin(void)
{
	t_minishell *msh;
	
	msh = g_getset(NULL);
	dup2(msh->stdio.stdin_fd, STDIN_FILENO);
	dup2(msh->stdio.stdout_fd, STDOUT_FILENO);
	dup2(msh->stdio.stderr_fd, STDERR_FILENO);
	close(msh->stdio.stdin_fd);
	close(msh->stdio.stdout_fd);
	close(msh->stdio.stderr_fd);
}

//copies (dup) each stdio file descriptor for each built-ins
//in order to not loose the stdio on parent proc
int redir_stdio_builtin(t_ast_node *node)
{
	t_minishell *msh;
	int redirs;

	msh = g_getset(NULL);
	msh->stdio.stdin_fd = dup(STDIN_FILENO);
	msh->stdio.stdout_fd = dup(STDOUT_FILENO);
	msh->stdio.stderr_fd = dup(STDERR_FILENO);
	if (msh->stdio.stdin_fd == -1 || msh->stdio.stderr_fd == -1 || msh->stdio.stdout_fd == -1)
		return (-1);
	redirs = redirections_handler(node);
	if (redirs !=0)
		return (restore_stdio_builtin(), redirs);
	return (redirs);
}

//calls the adequate built-in function
int	call_builtin(t_bi_type	builtin_type, t_ast_node *node)
{
	if (builtin_type == BUILTIN_ECHO)
		return (builtin_echo(node));
	if (builtin_type == BUILTIN_CD)
		return (builtin_cd(node));
	if (builtin_type == BUILTIN_PWD)
		return (builtin_pwd());
	if (builtin_type == BUILTIN_EXPORT)
		return (builtin_export(node));
	if (builtin_type == BUILTIN_UNSET)
		return (builtin_unset(node));
	if (builtin_type == BUILTIN_ENV)
		return (builtin_env());
	if (builtin_type == BUILTIN_EXIT)
		return (builtin_exit(node));
	return (1);
}

//return a built-in type from the name of exec cmd
t_bi_type	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

//built-ins have persistant impact on msh should run in parent
//(cd and ENV related built-ins like export and unset)
//other built-ins should run in a child to mimick bash's behavior (env)
int	run_builtin(t_bi_type	builtin_type, t_ast_node *node)
{
	int	exit_status;

	exit_status = redir_stdio_builtin(node);
	if (exit_status)
		return (exit_status);
	exit_status = call_builtin(builtin_type, node);
	restore_stdio_builtin();
	set_exitcode(exit_status);
	return (exit_status);
}

