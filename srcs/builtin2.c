/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:41:38 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 17:05:02 by souaret          ###   ########.fr       */
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
// #include <stdbool.h>
// #include <stddef.h>
// #include <string.h> // For strcmp

// Define a function pointer type for built-in commands
typedef int (*builtin_func)(char **args);

// Structure to associate a keyword with its function
typedef struct s_builtin
{
	const char      *keyword;
	builtin_func    func;
} t_builtin;

// Declare the built-in functions
int cmd_echo(char **args);
int cmd_cd(char **args);
int cmd_pwd(char **args);
int cmd_unset(char **args);
int cmd_export(char **args);
int cmd_env(char **args);
int cmd_exit(char **args);

// Array of built-in commands and their corresponding functions
const t_builtin g_builtins[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"export", cmd_export},
	{"env", cmd_env},
	{"exit", cmd_exit},
	{NULL, NULL} // Sentinel value to mark the end of the array
};

// Check if a command is a built-in
bool is_builtin(const char *cmd_str)
{
	int i = 0;

	if (cmd_str == NULL)
		return false;
	while (g_builtins[i].keyword != NULL)
	{
		if (strcmp(g_builtins[i].keyword, cmd_str) == 0)
			return true;
		i++;
	}
	return false;
}

// Execute a built-in command
int	cmd_exe_builtin(t_cmd *cmd)
{
	char **args = cmd->str;
	int i = 0;

	if (args == NULL || args[0] == NULL)
		return -1; // Error: No command provided

	while (g_builtins[i].keyword != NULL)
	{
		if (strcmp(g_builtins[i].keyword, args[0]) == 0)
			return g_builtins[i].func(args); // Call the corresponding function
		i++;
	}
	return -1; // Error: Command not found
}
