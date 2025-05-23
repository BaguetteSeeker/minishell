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

//returns position of a variable in ENV
int	var_pos(char **env, const char *var_name)
{
	int		i;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

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

//Either adds or modify an entry in ENV
//checks if var_name exists in ENV, if yes, modify its value
//else, write a new entry
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
		new_env = add_new_entry(env, new_entry);
	else
		new_env = replace_new_entry(env, new_entry, i);
	ft_free_dynarr(env);
	g_getset(NULL)->var_env = new_env;
}
