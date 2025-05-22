/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/20 12:57:03 by epinaud          ###   ########.fr       */
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
	if (msg && *msg)
		perror(msg);
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
		if (ft_strncmp(msh_g->input, "exit", 4) == 0)
			exit_shell(EXIT_MSG);
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
		//draw_ast(msh_g->cmd_table, "", 1);
		//ft_printf("\n ===== AST execution : =====\n");
		msh_g->last_exitcode = execute_node(msh_g->cmd_table);
		printf("\n ===== exit code is : %d =====\n", msh_g->last_exitcode);
		msh_g->state = MSH_EXECUTING;
		clean_routine();
	}
}

//faudrait mettre au clair la strat sur ENV et VAR, ou stocker quoi, etc..
//et bouger cette fonction parce qu'elle a rien a faire ici lol
char	**copy_env(char **env)
{
	size_t	i;
	size_t	count;
	char	**copy;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		put_err("ENV copy : Malloc Failure");
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

//TODO: Load ENV and SHELL variables into the global struct
/* Env tests :
	put_recurse_dynarr(g_getset(NULL)->var_env);
	ft_printf("Imported env has %u variables\n",
		ft_ptrlen((const void **)g_getset(NULL)->var_env));
				// parser(tokens);
*/
int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;

	(void)argc;
	(void)argv;
	(void)env;
	msh_g = g_getset(&(t_minishell){0});
	msh_g->var_env = copy_env(env);
	set_sigaction(&signals_handler);
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

	(not sure if this should be fixed)
	- on Uncatched error the parsing still quits
		example :
		copying some heavier expression into the shell, like C code or stuff that have tons of newline
	the output is "Uncatched Parsing Error :                       Expecting Operator token but none was provided: Success"

	exec errors
	-no echo :
		$_
		$?
		-n argument
	-exec_utils.c sucks
*/