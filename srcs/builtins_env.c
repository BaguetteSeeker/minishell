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

//Following three functions serve as an interface to ENV
//removes an entry in ENV if it exists
void	update_remove_env(char *var_name)
{
	char	**env;
	char	**new_env;

	env = g_getset(NULL)->var_env;
	new_env = write_remmove_env(env, var_name);
	if (new_env != env)
		ft_free_dynarr(env);
	g_getset(NULL)->var_env = new_env;
}

//returns a pointer to the variables entry if it exists in ENV
char	*get_var_env(char *var_name)
{
	int	i;
	char	**env;

	env = g_getset(NULL)->var_env;
	i = var_pos(g_getset(NULL)->var_env, var_name);
	if (i == -1)
		return (NULL);
	return (env[i]);
}

//returns a pointer to the the start of the value in the variable entry str
//'\0' if no value
char	*get_val_env(char *var_name)
{
	char	*value;
	char	*entry;

	entry = get_var_env(var_name);
	if (!entry)
		return(NULL);
	value = ft_strchr(entry, '=') + 1;
	return (value);
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
	int		i;
	char	**env;
	char	*new_entry;
	char	**new_env;

	env = g_getset(NULL)->var_env;
	new_entry = get_new_entry(var_name, value);
	new_env = NULL;
	i = var_pos(env, var_name);
	if (i == -1)
	{
		new_env = write_add_env(env, new_entry);
		ft_free_dynarr(env);
		g_getset(NULL)->var_env = new_env;
	}
	else
		add_new_entry(new_entry, env, new_env, i);
}
