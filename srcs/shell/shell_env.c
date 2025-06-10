/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 17:10:39 by epinaud          ###   ########.fr       */
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
void	update_shlvl(void)
{
	int		level;
	char	*shlvl;
	char	*new_shlvl;

	shlvl = get_var_value(VAR_ENV, "SHLVL");
	if (!shlvl)
		return ;
	level = ft_atoi(shlvl) + 1;
	new_shlvl = ft_itoa(level);
	if (!new_shlvl)
		put_err("strdup");
	update_add_var(VAR_ENV, "SHLVL", new_shlvl);
	free(new_shlvl);
}

//returns last argument of given node
void	update_underscore(t_ast_node *node)
{
	char	*last_arg;
	int		i;

	if (!node || node->type != NODE_COMMAND)
		return ;
	if (node->exp_args && node->exp_args[0])
	{
		i = ft_ptrlen((const void **)node->exp_args) - 1;
		last_arg = ft_strdup(node->exp_args[i]);
	}
	else if (node->value)
		last_arg = ft_strdup(node->value);
	else
	{
		update_add_var(VAR_ENV, "_", "");
		return ;
	}
	if (!last_arg)
		put_err("strdup");
	update_add_var(VAR_ENV, "_", last_arg);
	free(last_arg);
}
