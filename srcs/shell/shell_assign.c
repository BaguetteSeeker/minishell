/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/23 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int assign_noval(char *name)
{
	if (is_valid_export(name))
		update_add_var(name, "");
	else
	{
		ft_dprintf(STDERR_FILENO, ERRMSG_EXPORT, name);
		return (1);
	}
	return (0);
}

//exports VAR and assignes it a value
int	assign_val(char *arg, char *equal_sign)
{
	char	*var;
	char	*val;

	*equal_sign = '\0';
	var = arg;
	val = equal_sign + 1;
	if (is_valid_export(var))
		update_add_var(var, val);
	else
	{
		ft_dprintf(STDERR_FILENO, ERRMSG_EXPORT, val);
		*equal_sign = '=';
		return (1);
	}
	*equal_sign = '=';
	return (0);
}

int	assign_shell_var(t_ast_node *node)
{
	int		i;
	int		exit_code;
	char	*equal_sign;

	i = 0;
	exit_code = 0;
	while (node->vars && node->vars[i])
	{
		equal_sign = ft_strchr(node->vars[i], '=');
		if (equal_sign)
			exit_code |= assign_val(node->vars[i], equal_sign);
		else
			exit_code |= assign_noval(node->vars[i]);
		i++;
	}
	g_getset(NULL)->last_exitcode = exit_code;
	return (exit_code);
}