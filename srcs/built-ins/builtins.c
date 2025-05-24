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

int	ft_isnum(char *s)
{
	if (!s || *s == '\0')
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}


//built-ins have persistant impact on msh should run in parent
//(cd and ENV related built-ins like export and unset)
//other built-ins should run in a child to mimick bash's behavior
int	run_builtin(t_builtin_type	builtin_type, t_ast_node *node)
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

t_builtin_type	is_builtin(const char *cmd)
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

int	builtin_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}

int	builtin_env(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		put_recurse_dynarr(g_getset(NULL)->var_env);
		//debug
		printf("\n === VAR SHELL === \n");
		put_recurse_dynarr(g_getset(NULL)->var_shell);
		//to remove
		clean_shell();
		exit(0);
	}
	wait(NULL);
	return (0);
}

int	builtin_exit(t_ast_node *node)
{
	int	exit_code;

	if (!node->args || !node->args[0])
		exit_code = 0;
	else if (ft_ptrlen((const void **)node->args) != 1)
	{
		ft_putendl_fd("exit\nexit : too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (!ft_isnum(node->args[0]))
	{
		ft_putendl_fd("exit\nexit : numeric argument required", STDERR_FILENO);
		exit_shell(NULL, 2);
	}
	else
		exit_code = atoi(node->args[0]);
	//printf("\n\t\t%d\n\n", exit_code);
	if (exit_code == -1)
	{
		ft_putendl_fd("exit\nexit : numeric argument required", STDERR_FILENO);
		exit_shell(NULL, 2);
	}
	exit_shell(EXIT_MSG, exit_code);
	return (1);
}
