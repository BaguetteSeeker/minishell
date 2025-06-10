/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:11:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 23:07:18 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int sig)
{
	t_msh_state	msh_state;

	msh_state = g_getset(NULL)->state;
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDERR_FILENO);
		if (msh_state == MSH_PROMPTING || msh_state == MSH_PROMPTING_COMPLETION)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_getset(NULL)->signal = SIGINT;
		}
		else if (msh_state == MSH_HEREDOC)
			g_getset(NULL)->signal = SIGINT;
		else
			exit_shell(NO_EXIT_MSG, 0);
	}
	return ;
}

//Sets up custom handling for SIGINT and ignores SIGQUIT
void	set_sigaction(void (sighandle)(int))
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sighandle;
	if (sigaction(SIGINT, &act, NULL) < 0)
		return ;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		return ;
}
