/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:10:10 by souaret           #+#    #+#             */
/*   Updated: 2025/04/17 19:38:23 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************************
 * delete  cmd tree (all nodes)
*************************************************************************/
void	cmd_free_all(void)
{
	t_cmd	*cmd;

	cmd = cmd_get(NULL);
	do_check_error_exit((cmd == NULL), ERR_CMD_6);
	cmd_delete(cmd);
	cmd_set(NULL);
}

const char	*cmd_print(int cmd_id)
{
	if (cmd_id == CMD_ECHO)
		return ("echo");
	else if (cmd_id == CMD_PWD)
		return ("pwd");
	else if (cmd_id == CMD_CD)
		return ("cd");
	else if (cmd_id == CMD_EXPORT)
		return ("export");
	else if (cmd_id == CMD_UNSET)
		return ("unset");
	else if (cmd_id == CMD_ENV)
		return ("env");
	else if (cmd_id == CMD_EXIT)
		return ("exit");
	else
		return ("cmd:unknown");
}