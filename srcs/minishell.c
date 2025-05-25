/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/25 19:07:06 by epinaud          ###   ########.fr       */
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
		ft_putendl_fd(msg, 1);
	clean_shell();
	exit(EXIT_FAILURE);
}

void	exit_shell(bool output_msg)
{
	if (output_msg == EXIT_MSG)
		ft_putendl_fd("exit", STDOUT_FILENO);
	clean_shell();
	exit(EXIT_SUCCESS);
}

//Handles Minishell' routine
void	prompt_routine(t_minishell *msh_g)
{
	t_token		*tokens_tmp;

	while (1)
	{
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(PROMPT_NAME, ADD_HISTORY);
		msh_g->state = MSH_TOKENIZING;
		msh_g->tokens = tokenize(&msh_g->input, &msh_g->tokens);
		if (msh_g->state == MSH_FAILLURE)
		{
			clean_routine();
			continue ;
		}
		msh_g->state = MSH_EXPANDING;
		msh_lstiter(msh_g->tokens, &expand_token);
		//msh_lstiter(msh_g->tokens, &lst_put);
		msh_g->state = MSH_PARSING;
		tokens_tmp = msh_g->tokens;
		msh_g->cmd_table = parse_tokens(&tokens_tmp, NULL);
		//print_ast(msh_g->cmd_table);
		// ft_printf("\n ===== AST visual representation: =====\n");
		draw_ast(msh_g->cmd_table, "", 1);
		msh_g->state = MSH_EXECUTING;
		//ft_printf("\n ===== AST execution : =====\n");
		msh_g->last_exitcode = execute_node(msh_g->cmd_table);
		printf("\n ===== exit code is : %d =====\n", msh_g->last_exitcode);
		if (msh_g->last_exitcode == 0)
			update_underscore(msh_g->cmd_table);
		clean_routine();
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
	update_SHLVL();
	set_sigaction(&signals_handler);
	if (argc > 1)
		return (script_args_routine(msh_g, argc, argv));
    else if (!isatty(STDIN_FILENO))
		return (script_stdin_routine(msh_g));
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