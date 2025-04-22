/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:41:38 by souaret           #+#    #+#             */
/*   Updated: 2025/04/22 15:33:56 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
 * 
 * WARNING: 
 * This is alternate code for the builtin.c file.
 * It includes the same functionality
 * but is structured differently.
 * 
 * Only one versioon should go to production.
 *  
****************************************************************************/

/***************************************************************************
 * 
 * 
 * 
***************************************************************************/
t_builtin	*builtin_init(void)
{
	static t_builtin	g_builtin[] = {
	{"echo", CMD_ECHO, cmd_echo},
	{"cd", CMD_CD, cmd_cd},
	{"pwd", CMD_PWD, cmd_pwd},
	{"unset", CMD_UNSET, cmd_unset},
	{"export", CMD_EXPORT, cmd_export},
	{"env", CMD_ENV, cmd_env},
	{"exit", CMD_EXIT, cmd_exit},
	{NULL, CMD_ERROR, NULL} // Sentinel value to mark the end of the array
	};

	ft_printf("builtin_init\n");
	// ft_printf("<%s>\n", g_builtin[0].keyword);
	// ft_printf("<%s>\n", g_builtin[1].keyword);
	// ft_printf("<%s>\n", g_builtin[2].keyword);
	return (g_builtin);
}

/***************************************************************************
 * 
 * 
***************************************************************************/
t_builtin	*builtin_get(char *cmd_str)
{
	if (cmd_str == NULL)
		return (builtin_init());
	else
		do_error_exit(ERR_BUILTIN);
	return (NULL);
}

int	get_builtin_id(char *cmd_str)
{
	int			i;
	t_builtin	*g_builtin;

	g_builtin = builtin_get(NULL);
	if (cmd_str == NULL)
		return (CMD_ERROR);
	i = 0;
	while (g_builtin[i].keyword != NULL)
	{
		if (ft_strcmp(g_builtin[i].keyword, cmd_str) == 0)
			return (g_builtin[i].cmd_bi_id);
		i++;
	}
	return (CMD_ERROR);
}

/***************************************************************************
 * 
 *	// Check if a command is a built-in
 * 
***************************************************************************/
bool	is_builtin(char *cmd_str)
{
	int			i;
	t_builtin	*g_builtin;

	g_builtin = builtin_get(NULL);
	if (cmd_str == NULL)
		return (false);
	i = 0;
	while (g_builtin[i].keyword != NULL)
	{
		if (ft_strcmp(g_builtin[i].keyword, cmd_str) == 0)
			return (true);
		i++;
	}
	return (false);
}

/***************************************************************************
 * 
 *	// Execute a built-in command
 * 
***************************************************************************/
int	cmd_exe_builtin(t_cmd *cmd)
{
	char		**args;
	int			i;
	t_builtin	*g_builtin;

	g_builtin = builtin_get(NULL);
	args = cmd->cmd_args;
	if (args == NULL || args[0] == NULL)
		return (-1);
	i = 0;
	while (g_builtin[i].keyword != NULL)
	{
		if (ft_strcmp(g_builtin[i].keyword, args[0]) == 0)
			return (g_builtin[i].func(args)); // Call the corresponding function
		i++;
	}
	return (-1); // Error: Command not found
}
