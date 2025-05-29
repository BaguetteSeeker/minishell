/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:11:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 21:15:24 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_msh_state	msh_state;

	(void) context;
	(void) siginfo;
	msh_state = g_getset(NULL)->state;
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDERR_FILENO);
		if (msh_state == MSH_PROMPTING)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			exit_shell(NO_EXIT_MSG);
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
