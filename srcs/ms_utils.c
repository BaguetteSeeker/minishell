/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:57:30 by souaret           #+#    #+#             */
/*   Updated: 2025/04/14 14:31:15 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*****************************************************************************
 * 
 * Output Log Message: if flag is ON
 * 		otherwise, remain silent [off]
 * 
*****************************************************************************/
void	putlog_fd(char *log_message)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	if (!minishell)
		show_error_exit(ERR_7);
	if (minishell->log_msg)
		ft_putendl_fd(log_message, STDERR);
}
