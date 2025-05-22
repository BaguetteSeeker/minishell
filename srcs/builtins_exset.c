/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export VAR		adds "VAR=" to ENV
//export VAR=123	adds "VAR=123" to ENV
//export on a var that alread exists should be benign and change its value
//(tema comment cest clean ptn)
int	builtin_export(t_ast_node *node)
{
	int		i;
	char	*var;
	char	*val;
	char	*equal_sign;

	i = 0;
	while (node->args && node->args[i])
	{
		equal_sign = ft_strchr(node->args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0'; //du génie
			var = node->args[i];
			val = equal_sign + 1;
			update_add_env(var, val);
			*equal_sign = '=';
		}
		else
			update_add_env(node->args[i], "");
		i++;
	}
	return (0);
}

//unset VAR	removes VAR from ENV
//unset VAR	whereas VAR doesn't exist should be benign.
int	builtin_unset(t_ast_node *node)
{
	int	i;

	i = 0;
	while (node->args && node->args[i])
	{
		update_remove_env(node->args[i]);
		i++;
	}
	return (0);
}