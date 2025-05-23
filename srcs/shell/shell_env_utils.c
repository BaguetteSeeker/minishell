/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_entry(char *var_name, char *value)
{
	char	*buffer;
	char	*new_entry;

	buffer = ft_strjoin(var_name, "=");
	new_entry = ft_strjoin(buffer, value);
	free(buffer);
	return (new_entry);
}

char	**build_env_novar(char **env, int pos, int len)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != pos)
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

//on two following function, the caller shall free env
//if var_name exists, return env
//if not, construct a new env skipping it, returns new env
char	**write_remmove_env(char **env, char *var_name)
{
	int		len;
	int		pos;
	char	**new_env;

	pos = var_pos(env, var_name);
	if (pos == -1)
		return (env);
	len = 0;
	while (env[len])
		len++;
	new_env = build_env_novar(env, pos, len);
	return (new_env);
}

//copies env to new buffer, adds new_entry, free old buffer, return new buffer
char	**add_new_entry(char **env, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while(env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	return (new_env);
}
//copy ENV until entry found, copy new_entry (with new value)
//copy rest of ENV, returns new_env 
char	**replace_new_entry(char **env, char *new_entry, int i)
{
	int j;
	char	**new_env;

	j = 0;
	new_env = malloc(sizeof(char *) * (ft_ptrlen((const void **)env) + 1));	
	if (!new_env)
		return (NULL);
	while (env[j])
	{
		if (j == i)
			new_env[j] = new_entry;
		else
			new_env[j] = ft_strdup(env[j]);
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

