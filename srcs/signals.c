/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:50:11 by souaret           #+#    #+#             */
/*   Updated: 2025/04/22 18:55:41 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
 * 
 *  Subprocess interruption ?
 * 
****************************************************************************/
int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

/***************************************************************************
 * 
 * 
 * 
****************************************************************************/
void	set_signals_parent(void)
{
	struct sigaction	sa;

	g_signal = 0;
	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = if_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/***************************************************************************
 * 
 * 	// signal(SIGPIPE, exit_subshell);
 *	// signal(SIGTSTP, SIG_IGN);
 * 
****************************************************************************/
void	set_signals_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}


/***************************************************************************
 * 
 * 
 * 
****************************************************************************/
void	set_signals_subshell(void)
{
	signal(SIGQUIT, exit_subshell);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, exit_subshell);
}

/***************************************************************************
 * 
 *  Subprocess interruption ?
 * 
****************************************************************************/
void	if_sigint(int sig)
{
	g_signal = 128 + sig;
	rl_done = 1;
	last_status_code(128 + sig, SET);
}
