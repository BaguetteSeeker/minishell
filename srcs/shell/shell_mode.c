/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//joins every argument as a single line to simulate single prompt
void script_args_routine(t_minishell *msh_g, int argc, char **argv)
{
	char	*input;

	msh_g->mode = SCRIPT_ARGV;
	input = ft_strdup(argv[1]);
	if (!input)
		put_err("strdup");
	if (!(*input))
	{
		ft_putendl_fd("msh: : command not found", STDERR_FILENO);
		clean_shell();
		exit(127);
	}
	for (int i = 2; i < argc; i++)
	{
		char *tmp = input;
		input = ft_strjoin(input, " ");
		free(tmp);
		tmp = input;
		input = ft_strjoin(input, argv[i]);
		free(tmp);
	}
	msh_g->input = input;
	repl_once(msh_g);
	exit_shell(NULL, msh_g->last_exitcode);
}


static char	*read_and_prepare_line(size_t len)
{
	char	*line;
	char	*input;

	line = get_next_line(0);
	while (line && *line == '\0')
	{
		free(line);
		line = get_next_line(0);
	}
	if (!line)
		return (NULL);
	input = ft_strdup(line);
	if (!input)
		put_err("strdup");
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	free(line);
	return (input);
}

//extract lines from stdin line by line untile !line (EOF reached)
//for each line, execute as a regular single prompt
void	script_stdin_routine(t_minishell *msh_g)
{
	char	*line;
	size_t	len;

	msh_g->mode = SCRIPT_STDIN;
	len = msh_g->input ? ft_strlen(msh_g->input) : 0;
	line = read_and_prepare_line(len);
	while (line)
	{
		msh_g->input = line;
		repl_once(msh_g);
		line = read_and_prepare_line(len);
	}
	exit_shell(NULL, msh_g->last_exitcode);
}
