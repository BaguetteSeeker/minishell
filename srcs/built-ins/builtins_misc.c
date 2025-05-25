/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 is all char of C string are integers
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

//prints the current working directory to stdout
int	builtin_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}

//prints ENV to stdout
//to mimick bash, runs command in a child-process
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

//exits the shell
//	-exit (integer)		exits the shell with integer exit status
//	-exit (non-integer)	exits the shell with exit code 2
//	-exit arg arg		returns 1, doesnt exit the shell
int	builtin_exit(t_ast_node *node)
{
	int	exit_code;

	if (!node->args || !node->args[0])
		exit_code = 0;
	else if (!ft_isnum(node->args[0]))
	{
		ft_putendl_fd("exit\nexit : numeric argument required", STDERR_FILENO);
		exit_shell(NULL, 2);
	}
	else if (ft_ptrlen((const void **)node->args) != 1)
	{
		ft_putendl_fd("exit\nexit : too many arguments", STDERR_FILENO);
		return (1);
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