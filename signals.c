/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:11:49 by epinaud           #+#    #+#             */
/*   Updated: 2025/01/24 13:19:01 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	if (sig == SIGINT)
	{
		//CTRL-C in interractive : print previous prompt without exec then output a new clean prompt
		//CTRL-C in execution : exit with error
	}
	else if (sig == SIGQUIT)
	{
		//CTRL-D in interractive : exit current terminal
		//CTRL-D in exec : exit with error
		//ctrl-\ in interractive : nullified
		//ctrl-\ in execution : exec with error and core dump
	}
	return ;
}

void	set_sigaction(void (sighandle)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sighandle;
	if (sigaction(SIGINT, &act, NULL) < 0)
		return ;
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		return ;
}