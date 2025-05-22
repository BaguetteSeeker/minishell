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
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	return (1);
}

//echo (some) (text)	outputs text on stdin
//echo -n (some) (text)	outputs text on stdin without newline
//echo -n -n (text)		is valid !!!
//echo -n (text) -n		does print the -n though
//exho -nnnn -coucou	outputs "-coucou" (wtf ??)
int	builtin_echo(t_ast_node *node)
{
	int		i = 0;
	int		newline = 1;

	while (node->args[i] && has_echo_n(node->args[i]))
	{
		newline = 0;
		i++;
	}
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], STDOUT_FILENO);
		if (node->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
