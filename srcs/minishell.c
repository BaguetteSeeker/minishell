/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/10 14:18:42 by epinaud          ###   ########.fr       */
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

char	*open_prompt(char *prompt, size_t history)
{
	char	*input_line;

	input_line = readline(prompt);
	if (input_line == NULL)
		return (exit_shell(), NULL);
	else if (history == ADD_HISTORY && *input_line)
		add_history(input_line);
	return (input_line);
}

void	exit_shell(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	clean_shell();
	exit(EXIT_SUCCESS);
}
// put_recurse_dynarr(g_getset(NULL)->var_env);
// ft_printf("Imported env has %u variables\n",
	// ft_ptrlen((const void **)g_getset(NULL)->var_env));
			// // parser(tokens);
//Handles Minishell' routine
void	prompt_routine(t_minishell *msh_g)
{
	t_token		*tokens_tmp;
	
	while (1)
	{
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(PROMPT_NAME, ADD_HISTORY);
		if (ft_strncmp(msh_g->input, "exit", 4) == 0)
			exit_shell();
		msh_g->state = MSH_TOKENIZING;
		msh_g->tokens = tokenize(&msh_g->input, msh_g->tokens);
		handle_heredocs(msh_g->tokens);
		ft_lstiter(msh_g->tokens, &expand_token);
		ft_lstiter(msh_g->tokens, &lst_put);
		msh_g->state = MSH_PARSING;
		tokens_tmp = msh_g->tokens;
		msh_g->cmd_table = parse_tokens(&tokens_tmp, NULL);
		print_ast(msh_g->cmd_table);
		msh_g->state = MSH_EXECUTING;
		clean_routine();
		msh_g->tokens = NULL;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;

	(void)argc;
	(void)argv;
	(void)env;
	msh_g = g_getset(&(t_minishell){0});
	set_sigaction(&signals_handler);
	//msh_g->var_env = env;
	prompt_routine(msh_g);
	return (0);
}
