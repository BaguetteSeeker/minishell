/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/26 18:33:47 by epinaud          ###   ########.fr       */
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

//Handles Minishell' routine
void	prompt_routine(t_minishell *msh_g)
{
	msh_g->mode = INTERACTIVE;
	while (1)
	{
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(PROMPT_NAME, ADD_HISTORY);
		repl_once(msh_g);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;

	(void)argc;
	(void)argv;
	(void)env;
	msh_g = g_getset(&(t_minishell){0});
	msh_g->var_env = copy_env(env);
	msh_g->var_shell = init_var_shell();
	update_SHLVL();
	set_sigaction(&signals_handler);
	if (argc > 1)
        return (script_args_routine(msh_g, argc, argv), 1);
    else if (!isatty(STDIN_FILENO))
		return (script_stdin_routine(msh_g), 1);
	else
		prompt_routine(msh_g);
	return (0);
}

/*
	parsing errors
	- redirections should be parsed wherever they are inside the chain of arguments
		examples :
		ls > file1 -la
		(works as "ls -la > file1")
		< Makefile cat | head -n > file1 1
		(works as "cat < Makefile  | head -n 1 > file1")
	basically, parsing logic is :
		-everything counts as a program argument, until a redirection character is found
		-if token <, >, << or >> is found, next token is the file (or delimiter) of the redirection

	- on Uncatched error the parsing still quits
		example prompting :
		"node->right = parse_tokens(tokens, node->right);"
		copying some heavier expression into the shell, like C code or stuff that have tons of newline
	the output is "Uncatched Parsing Error :                       Expecting Operator token but none was provided: Success"
	
	- on catched error, the parsing seems broken
		example prompting :
		"a00))'a ' a'a  / \\ 1= _+ =-2=2-1"
	outputs :
		syntax error near unexpected token `)'
	then entering other command 
		$minishell: exit
		msh: syntax error near unexpected token `exit'
	eh

	exec errors
	-exec_utils.c still sucks
	-cannot open file.sh passed as argument

	idea :
	-cd with dir display
*/