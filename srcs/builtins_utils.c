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

char	*get_new_entry(char *var_name, char *value)
{
	char	*buffer;
	char	*new_entry;

	buffer = ft_strjoin(var_name, "=");
	new_entry = ft_strjoin(buffer, value);
	free(buffer);
	return (new_entry);
}

//construct new env skipping var_name, free old env, returns it
char	**write_remmove_env(char **env, char *var_name)
{
	int		i;
	int		j;
	int		len;
	int		pos;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	pos = var_pos(env, var_name);
	if (pos == -1)
		return (free(new_env), env);
	j = 0;
	i = 0;
	while (j < len)
	{
		if (j != pos)
			new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}

//copies env to new buffer, adds new_entry, free old buffer, return new buffer
char	**write_add_env(char **env, char *new_entry)
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
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}


