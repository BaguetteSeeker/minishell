/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/06/09 21:22:09 by epinaud          ###   ########.fr       */
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

void	exit_shell(bool output_msg, int exit_code)
{
	if (output_msg == EXIT_MSG)
		ft_putendl_fd("exit", STDERR_FILENO);
	clean_shell();
	exit((unsigned char)exit_code);
}

static void	msh_set_canonical(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	usage_error(void)
{
	ft_dprintf(STDERR_FILENO, "msh: -c: option requires an argument\n");
	exit_shell(NO_EXIT_MSG, 2);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;

	(void)argv;
	msh_g = g_getset(&(t_minishell){0});
	msh_set_canonical();
	msh_g->var_env = copy_env(env);
	msh_g->var_shell = init_shell_var();
	update_shlvl();
	update_add_var(VAR_ENV, "_", argv[0]);
	update_add_var(VAR_SHELL, "?", "0");
	set_sigaction(&signals_handler);
	if (argc > 1)
	{
		if (strcmp(argv[1], "-c") == 0 )
		{
			if (argc == 2)
				return (usage_error(), 1);
			else
				return (script_string_routine(msh_g, argc, argv), 1);
		}
		else
			return (script_file_routine(msh_g, argv[1]), 1);
	}
	else if (!isatty(STDIN_FILENO))
		return (script_stdin_routine(msh_g), 1);
	else
		prompt_routine(msh_g);
	return (0);
}
