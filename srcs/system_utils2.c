/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:38 by souaret           #+#    #+#             */
/*   Updated: 2025/04/24 14:38:07 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * 
 * output Log Message: if flag is ON
 *		otherwise, remain silent [off]
 * 
*****************************************************************************/
void	putlog_fd(char *log_message)
{
	t_ms	*ms;

	ms = ms_get(NULL);
	if (!ms)
		do_error_exit(ERR_EXEC_4);
	if (ms->log_msg)
		ft_putendl_fd(log_message, STDERR_FILENO);
}
