/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:11:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/23 20:20:11 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (sig == SIGINT)
	{
		if (g_getset(NULL)->state == MSH_BLOCKING_PROMPT)
			exit_shell(NO_EXIT_MSG, 0);
		ft_putendl_fd("", STDOUT_FILENO);
		if (g_getset(NULL)->state == MSH_BLOCKING_PROMPT)
			exit_shell(NO_EXIT_MSG, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

//Sets up custom handling for SIGINT and ignores SIGQUIT
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
