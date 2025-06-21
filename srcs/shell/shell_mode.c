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

//script args routine
static char	*join_args(int argc, char **argv)
{
	int		i;
	char	*input;
	char	*tmp;

	i = 3;
	input = ft_strdup(argv[2]);
	if (!input)
		put_err("strdup");
	while (i < argc)
	{
		tmp = input;
		input = ft_strjoin(input, " ");
		free(tmp);
		tmp = input;
		input = ft_strjoin(input, argv[i]);
		free(tmp);
		i++;
	}
	return (input);
}

//joins every argument as a single line to simulate single prompt
void	script_string_routine(t_minishell *msh_g, int argc, char **argv)
{
	char	*input;

	msh_g->mode = SCRIPT_ARGV;
	input = join_args(argc, argv);
	if (!(*input))
	{
		ft_dprintf(STDERR_FILENO, ERRMSG_NOCMD, "");
		clean_shell();
		exit(127);
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

void script_file_routine(t_minishell *msh_g, const char *file)
{
    int fd;
	
	if (access(file, F_OK) != 0
		|| access(file, R_OK) != 0)
	{
		ft_dprintf(2, ERRMSG_NOFILE, file);
		exit_shell(NO_EXIT_MSG, EXITC_NOCMD);
	}
	if (access(file, X_OK) != 0)
	{
		ft_dprintf(2, ERRMSG_NOFILE, file);
		exit_shell(NO_EXIT_MSG, EXITC_NOEXEC);
	}
	fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    script_stdin_routine(msh_g);
}

//extract lines from stdin line by line untile !line (EOF reached)
//for each line, execute as a regular single prompt
void	script_stdin_routine(t_minishell *msh_g)
{
	char	*line;
	size_t	len;

	msh_g->mode = SCRIPT_STDIN;
	if (msh_g->input)
		len = ft_strlen(msh_g->input);
	else
		len = 0;
	line = read_and_prepare_line(len);
	while (line)
	{
		msh_g->input = line;
		repl_once(msh_g);
		line = read_and_prepare_line(len);
	}
	exit_shell(NULL, msh_g->last_exitcode);
}
