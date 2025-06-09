/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/06/09 12:22:27 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_getset(void *g)
{
	static t_minishell	*stored_g = {NULL};

	if (!stored_g)
		stored_g = g;
	return (stored_g);
}

void	put_err(char *msg)
{
	if (errno)
		perror(msg);
	else if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	clean_shell();
	exit(EXIT_FAILURE);
}

void	exit_shell(bool output_msg)
{
	if (output_msg == EXIT_MSG)
		ft_putendl_fd("exit", STDERR_FILENO);
	clean_shell();
	exit(EXIT_SUCCESS);
}

static void	msh_set_canonical(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;

	(void)argc;
	(void)argv;
	(void)env;
	msh_g = g_getset(&(t_minishell){0});
	msh_set_canonical();
	set_sigaction(&signals_handler);
	prompt_routine(msh_g);
	return (0);
}
