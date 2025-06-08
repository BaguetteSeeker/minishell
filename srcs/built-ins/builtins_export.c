/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exports VAR in var_env, and assignes it a value
//temp split using equal_sign
//bash-like quote handling on assign thanks to strip_outquotes
int	export_val(char *arg, char *equal_sign)
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
	update_add_var(VAR_ENV, var, clean_val);
	*equal_sign = '=';
	free(clean_val);
	return (0);
}

//moves an entry from var_shell to var_env
void	move_entry(char *entry)
{
	int		len;
	char	*equal_sign;
	char	*shell_entry;
	char	*var_name;

	equal_sign = ft_strchr(entry, '=');
	
	shell_entry = get_var_entry(VAR_SHELL, entry);
	len = ft_strlen(entry);
	if (equal_sign)
		len = equal_sign - entry;
	var_name = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(var_name, shell_entry, len + 1);
	update_add_var(VAR_ENV, var_name, get_var_value(VAR_SHELL, var_name));
	update_remove_var(VAR_SHELL, var_name);
	free(var_name);
}

//if var already exists in shell_env, should be benign and change its value
//if var exists in shell_var
//	-if no value provided, moves it in shell_env
//	-if value provided, overwrite said value and moves it to shell_env
int	export_loop(char *arg)
{
	int		exit_code;
	char	*equal_sign;
	char	*new_entry;

	exit_code = 0;
	new_entry = NULL;
	if (get_var_entry(VAR_SHELL, arg))
	{
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			new_entry = ft_strdup(arg);
			update_remove_var(VAR_SHELL, arg);
		}
		else
			return (move_entry(arg), exit_code);
	}
	if (new_entry)
		arg = new_entry;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		exit_code = export_val(arg, equal_sign);
	return (free(new_entry), exit_code);
}

//exports a variable into shell_env
//	-export VAR		does nothing
//	-export VAR=123	adds "VAR=123" to shell_env
//	-export VAR whereas VAR exists in shell_var moves it to shell_env
int	builtin_export(t_ast_node *node)
{
	int		i;
	int		exit_code;
	char	**args;

	i = 1;
	exit_code = 0;
	args = node->exp_args;
	if (!node->exp_args || !node->exp_args[0])
		args = node->vars;
	while (args && args[i])
	{
		if (is_valid_var_name(args[i]))
		{
			if (export_loop(args[i]) != 0)
				exit_code = 1;
		}
		else
		{
			ft_dprintf(STDERR_FILENO, ERRMSG_EXPORT, args[i]);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}

//removes an entry from var_env or var_shell
//unset VAR	removes VAR from var_shell or var_env
//unset VAR	whereas VAR doesn't exist should be benign.
int	builtin_unset(t_ast_node *node)
{
	int	i;

	i = 1;
	while (node->exp_args && node->exp_args[i])
	{
		update_remove_var(VAR_SHELL, node->exp_args[i]);
		update_remove_var(VAR_ENV, node->exp_args[i]);
		i++;
	}
	return (0);
}