/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/25 17:43:37 by epinaud          ###   ########.fr       */
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
		msh_lstiter(msh_g->tokens, &lst_put);
		msh_g->state = MSH_PARSING;
		tokens_tmp = msh_g->tokens;
		msh_g->cmd_table = parse_tokens(&tokens_tmp, NULL);
		print_ast(msh_g->cmd_table);
		msh_g->state = MSH_EXECUTING;
		clean_routine();
	}
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
	// msh_g->var_env = env;
	set_sigaction(&signals_handler);
	prompt_routine(msh_g);
	return (0);
}
