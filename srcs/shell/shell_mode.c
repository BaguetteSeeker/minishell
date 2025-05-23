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
int script_args_routine(t_minishell *msh_g, int argc, char **argv)
{
	char	*input;

	input = ft_strdup(argv[1]);
	if (!input)
		put_err("strdup");
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
	return (msh_g->last_exitcode);
}

//extract lines from stdin line by line untile !line (EOF reached)
//for each line, execute as a regular single prompt
int script_stdin_routine(t_minishell *msh_g)
{
	char	*line;
	size_t	len;

	len = ft_strlen(msh_g->input);
	line = get_next_line(0);
	while (line)
	{
		if (!line || *line == '\0')
		{
			free(line);
			continue;
		}
		msh_g->input = ft_strdup(line);
		if (!msh_g->input)
			put_err("strdup");
		if (len > 0 && msh_g->input[len - 1] == '\n')
			msh_g->input[len - 1] = '\0';
		free(line);
		line = NULL;
		repl_once(msh_g);
		line = get_next_line(0);
	}
	return (msh_g->last_exitcode);
}
