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

//variable name should start with a letter
//variable names can only contain letter, digits and underscore
int	is_valid_var_name(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	assign_noval(char *name)
{
	if (is_valid_var_name(name))
		update_add_var(VAR_SHELL, name, "");
	else
	{
		return (1);
	}
	return (0);
}

//exports VAR and assignes it a value
int	assign_val(char *arg, char *equal_sign)
{
	char	*var;
	char	*val;
	char	*clean_val;

	*equal_sign = '\0';
	var = arg;
	val = equal_sign + 1;
	clean_val = ft_strdup(val);
	if (!clean_val)
		return (put_err("strdup"), 1);
	strip_outquotes(clean_val);
	if (is_valid_var_name(var))
		update_add_var(VAR_SHELL, var, clean_val);
	else
	{
		*equal_sign = '=';
		free(clean_val);
		return (1);
	}
	*equal_sign = '=';
	free(clean_val);
	return (0);
}

//assigns a value in var_shell
//	-if var exists in env, modifies it in var_env
int	assign_shell_var(t_ast_node *node)
{
	int		i;
	int		exit_code;
	char	*equal_sign;
	char	*is_env;

	i = 0;
	exit_code = 0;
	while (node->vars && node->vars[i])
	{
		is_env = get_var_entry(VAR_ENV, node->vars[i]);
		if (is_env)
			return (builtin_export(node));
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

//here, we should eventually change vars into exp_vars
//before that : 
//	-the expand_vars function must be well tested
//	-the command node without node->args (so assignement only) execution logic
//	  must be better understood (and maybe rewritten bc its not great)
//		in exec.c:62 command_no_command()