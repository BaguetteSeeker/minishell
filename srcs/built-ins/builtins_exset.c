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

//variable name should start with a letter
//variable names can only contain letter, digits and underscore
int	is_valid_export(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//exports VAR with no value
int	export_noval(char *name)
{
	if (is_valid_export(name))
		update_add_env(name, "");
	else
	{
		ft_dprintf(STDERR_FILENO, ERRMSG_EXPORT, name);
		return (1);
	}
	return (0);
}

//exports VAR and assignes it a value
int	export_val(char *arg, char *equal_sign)
{
	char	*var;
	char	*val;

	*equal_sign = '\0';
	var = arg;
	val = equal_sign + 1;
	if (is_valid_export(var))
		update_add_env(var, val);
	else
	{
		ft_dprintf(STDERR_FILENO, ERRMSG_EXPORT, val);
		*equal_sign = '=';
		return (1);
	}
	*equal_sign = '=';
	return (0);
}

//export VAR		adds "VAR=" to ENV
//export VAR=123	adds "VAR=123" to ENV
//export on a var that alread exists should be benign and change its value
int	builtin_export(t_ast_node *node)
{
	int		i;
	int		result;
	char	*equal_sign;

	i = 0;
	result = 0;
	while (node->args && node->args[i])
	{
		equal_sign = ft_strchr(node->args[i], '=');
		if (equal_sign)
			result |= export_val(node->args[i], equal_sign);
		else
			result |= export_noval(node->args[i]);
		i++;
	}
	return (result);
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