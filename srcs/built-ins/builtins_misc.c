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
	put_recurse_dynarr(g_getset(NULL)->var_env);
	//debug
	// printf("\n === VAR SHELL === \n");
	// put_recurse_dynarr(g_getset(NULL)->var_shell);
	//to remove
	return (0);
}


//helper to validate and parse an optional signed integer
//last line is casting code into an int
//bitwise operator & effectively gives the result modulo 256
static int	parse_exit_code(const char *str, int *code_out)
{
	long	sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (1); // invalid double sign
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	*code_out = (int)((sign * res) & 255);
	return (0);
}


//exits the shell
//	-exit (integer)		exits the shell with integer exit status
//	-exit (non-integer)	exits the shell with exit code 2
//	-exit arg arg		returns 1, doesnt exit the shell
int	builtin_exit(t_ast_node *node)
{
	int	exit_code;
	char **args = node->exp_args;

	if (!args || !args[1])
		exit_code = 0;
	else if (*node->exp_args[1] == '\0' || parse_exit_code(args[1], &exit_code))
	{
		ft_putendl_fd("exit\nexit : numeric argument required", STDERR_FILENO);
		restore_stdio_builtin();
		exit_shell(NULL, 2);
	}
	else if (ft_ptrlen((const void **)args) > 2)
	{
		ft_putendl_fd("exit\nexit : too many arguments", STDERR_FILENO);
		restore_stdio_builtin();
		return (1);
	}
	restore_stdio_builtin();
	exit_shell("exit", exit_code);
	return (0);
}
