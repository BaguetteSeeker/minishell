/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export VAR should add "VAR=" to ENV
//export VAR=123 should add "VAR=123" to ENV
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


//unset VAR should remove VAR from ENV
//unset VAR whereas VAR doesn't exist should be benign.
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

//Following two functions serve as an interface to ENV
//removes an entry in ENV if it exists
void	update_remove_env(char *var_name)
{
	char	**env;
	char	**new_env;

	env = g_getset(NULL)->var_env;
	new_env = write_remmove_env(env, var_name);
	free(env);
	g_getset(NULL)->var_env = new_env;
}

//Either adds or modify an entry in ENV
//checks if var_name exists in ENV, if yes, modify its value
//else, right a new entry
void	update_add_env(char *var_name, char *value)
{
	char	**env;
	char	**new_env;
	char	*new_entry;
	int		i;

	env = g_getset(NULL)->var_env;
	new_entry = get_new_entry(var_name, value);
	i = var_pos(env, var_name);
	if (i == -1)
		new_env = write_add_env(env, new_entry);
	else
	{
		free(env[i]);
		env[i] = new_entry;
		return ;
	}
	g_getset(NULL)->var_env = new_env;
}