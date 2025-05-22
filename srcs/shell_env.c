/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//faudrait mettre au clair la strat sur ENV et VAR, ou stocker quoi, etc..
//et bouger cette fonction parce qu'elle a rien a faire ici lol
char	**copy_env(char **env)
{
	size_t	i;
	size_t	count;
	char	**copy;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		put_err("ENV copy : Malloc Failure");
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

//increment SHLVL and overwrites it in ENV
void	update_SHLVL()
{
	int		level;
	char	*SHLVL;
	char	*new_SHLVL;

	SHLVL = get_val_env("SHLVL");
	if (!SHLVL)
		return ;
	level = ft_atoi(SHLVL) + 1;
	new_SHLVL = ft_itoa(level);
	update_add_env("SHLVL", new_SHLVL);
	free(new_SHLVL);
}

//returns last argument of given node
void	update_underscore(t_ast_node *node)
{
	int		i;
	char	*last_arg;

	if (!node || node->type != NODE_COMMAND || !node->args)
		return ;
	i = 0;
	while (node->args[i])
		i++;
	if (i > 0)
		last_arg = ft_strdup(node->args[i - 1]);
	else
		last_arg = ft_strdup(node->value);
	
	update_add_env("_", last_arg);
}
