/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:11:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/11 17:46:33 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		g_signal = 0;
void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (sig == SIGINT)
	{
		g_signal = 0;
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 0;
		// ft_putendl_fd("Handling SIGQUIT", 1);
	}
	return ;
}

void	set_sigaction(void (sighandle)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = sighandle;
	if (sigaction(SIGINT, &act, NULL) < 0)
		return ;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		return ;
}