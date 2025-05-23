/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/23 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
var stored in var_shell :
	- ?
	- PS1
	- PS2

	very special expension (not sure if mandatory)
	- ~
*/

void	udapte_var_shell(void)
{
	update_var_exitcode();
	//add other variables like PS1, PS2 for custom pompt
}

char	**init_var_shell(void)
{
	char	**var_shell;

	var_shell = malloc(sizeof(char *) * 4);
	if (!var_shell)
		return (NULL);
	var_shell[0] = ft_strdup("TEST=var_shell_test");
	var_shell[1] = ft_strdup("PS1=minishell$ ");
	var_shell[2] = ft_strdup("PS2=> ");
	var_shell[3] = ft_strdup("?=0");
	var_shell[4] = NULL;
	return (var_shell);
}

void	update_add_var(char *var_name, char *value)
{
	int		i;
	char	**var_shell;
	char	*new_entry;
	char	**new_var_shell;

	var_shell = g_getset(NULL)->var_shell;
	new_entry = get_new_entry(var_name, value);
	new_var_shell = NULL;
	i = var_pos(var_shell, var_name);
	if (i == -1)
		new_var_shell = add_new_entry(var_shell, new_entry);
	else
		new_var_shell = replace_new_entry(var_shell, new_entry, i);
	ft_free_dynarr(var_shell);
	g_getset(NULL)->var_shell = new_var_shell;
}

void	update_var_exitcode(void)
{
	int		exitcode;
	char	*var_exitcode;

	exitcode = g_getset(NULL)->last_exitcode;
	var_exitcode = ft_itoa(exitcode);
	update_add_var("?", var_exitcode);
	free(var_exitcode);
}