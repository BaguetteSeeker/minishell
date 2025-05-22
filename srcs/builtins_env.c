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

//Following two functions serve as an interface to ENV
//removes an entry in ENV if it exists
void	update_remove_env(char *var_name)
{
	char	**env = g_getset(NULL)->var_env;
	char	**new_env = write_remmove_env(env, var_name);
	if (new_env != env)
		ft_free_dynarr(env);
	g_getset(NULL)->var_env = new_env;
}

//update_add_env helper
void	add_new_entry(char *new_entry, char **env, char **new_env, int i)
{
	int j;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_ptrlen((const void **)env) + 1));
	if (!new_env)
		return ;
	while (env[j])
	{
		if (j == i)
			new_env[j] = new_entry;
		else
			new_env[j] = ft_strdup(env[j]);
		j++;
	}
	new_env[j] = NULL;
	ft_free_dynarr(env);
	g_getset(NULL)->var_env = new_env;
}

//Either adds or modify an entry in ENV
//checks if var_name exists in ENV, if yes, modify its value
//else, right a new entry
void	update_add_env(char *var_name, char *value)
{
	char	**env = g_getset(NULL)->var_env;
	char	**new_env;
	char	*new_entry = get_new_entry(var_name, value);
	int		i = var_pos(env, var_name);

	new_env = NULL;
	if (i == -1)
	{
		new_env = write_add_env(env, new_entry);
		ft_free_dynarr(env);
		g_getset(NULL)->var_env = new_env;
	}
	else
		add_new_entry(new_entry, env, new_env, i);
}


