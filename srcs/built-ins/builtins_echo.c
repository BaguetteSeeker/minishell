/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks -n argument
int	has_echo_n(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_print(t_ast_node *node, int i)
{
	ft_dprintf(STDOUT_FILENO, node->exp_args[i]);
	if (node->exp_args[i + 1])
		ft_dprintf(STDOUT_FILENO, " ");
}

//prints some text on stdout
//	-echo (some) (text)	outputs text on stdin
//	-echo -n (some) (text)	outputs text on stdin without newline
//	-echo -n -n (text)		is valid !!! only first concecutive -n count
//	-echo -nnnn -coucou	outputs "-coucou" (wtf ??)
int	builtin_echo(t_ast_node *node)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (!node->exp_args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	while (node->exp_args[i] && has_echo_n(node->exp_args[i]))
	{
		newline = 0;
		i++;
	}
	while (node->exp_args[i])
	{
		echo_print(node, i);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
