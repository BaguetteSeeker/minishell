/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable_interface.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Following functions serve as an interface to var_env and var_shell
//removes an entry in ENV if it exists
void	update_remove_var(int mode, char *var_name)
{
	char	**new_var_tab;
	char	**var_tab;

	if (mode == VAR_ENV)
		var_tab = g_getset(NULL)->var_env;
	else if (mode == VAR_SHELL)
		var_tab = g_getset(NULL)->var_shell;
	new_var_tab = write_remmove_env(var_tab, var_name);
	if (new_var_tab != var_tab)
		ft_free_dynarr(var_tab);
	if (mode == VAR_ENV)
		g_getset(NULL)->var_env = new_var_tab;
	else if (mode == VAR_SHELL)
		g_getset(NULL)->var_shell = new_var_tab;
}

//Either adds or modify an entry in ENV
//checks if var_name exists in ENV, if yes, modify its value
//else, write a new entry
void	update_add_var(int mode, char *var_name, char *value)
{
	int		i;
	char	*new_entry;
	char	**new_var_tab;
	char	**var_tab;

	if (mode == VAR_ENV)
		var_tab = g_getset(NULL)->var_env;
	else if (mode == VAR_SHELL)
		var_tab = g_getset(NULL)->var_shell;
	new_entry = get_new_entry(var_name, value);
	new_var_tab = NULL;
	i = var_pos(var_tab, var_name);
	if (i == -1)
		new_var_tab = add_new_entry(var_tab, new_entry);
	else
		new_var_tab = replace_new_entry(var_tab, new_entry, i);
	ft_free_dynarr(var_tab);
	if (mode == VAR_ENV)
		g_getset(NULL)->var_env = new_var_tab;
	else if (mode == VAR_SHELL)
		g_getset(NULL)->var_shell = new_var_tab;
}

//returns position of a variable in ENV
int	var_pos(char **var_tab, const char *var_name)
{
	int		i;
	int		len;
	char	*equal_sign;

	i = 0;
	equal_sign = ft_strchr(var_name, '=');
	len = ft_strlen(var_name);
	if (equal_sign)
		len = equal_sign - var_name;
	if (!var_tab)
		return (-1);
	while (var_tab[i])
	{
		if (ft_strncmp(var_tab[i], var_name, len) == 0
			&& var_tab[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//returns a pointer to the variables entry if it exists in ENV
char	*get_var_entry(int mode, char *var_name)
{
	int		i;
	char	**var_tab;

	if (mode == VAR_ENV)
		var_tab = g_getset(NULL)->var_env;
	else if (mode == VAR_SHELL)
		var_tab = g_getset(NULL)->var_shell;
	i = var_pos(var_tab, var_name);
	if (i == -1)
		return (NULL);
	return (var_tab[i]);
}

//returns a pointer to the the start of the value in the variable entry str
//'\0' if no value
char	*get_var_value(int mode, char *var_name)
{
	char	*value;
	char	*entry;

	entry = get_var_entry(mode, var_name);
	if (!entry)
		return (NULL);
	value = ft_strchr(entry, '=') + 1;
	return (value);
}
