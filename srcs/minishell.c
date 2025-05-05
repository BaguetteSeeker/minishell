/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/05 22:30:28 by epinaud          ###   ########.fr       */
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
		return (free(input_line), put_err("Readline faillure\n"), NULL);
	else if (history == ADD_HISTORY && *input_line)
		add_history(input_line);
	return (input_line);
}

// void	expand_node(t_ast_node *node)
// {
// 	node->value = expand(node->value);
// 	node.
// }

void	expand_token(t_token *tokens)
{
	if (tokens->type == DLESS)
		tokens->value = expand(tokens->value, XPD_HDOC);
	else
		tokens->value = strip_outquotes(expand(tokens->value, XPD_ALL));
}

// put_recurse_dynarr(g_getset(NULL)->var_env);
// ft_printf("Imported env has %u variables\n",
	// ft_ptrlen((const void **)g_getset(NULL)->var_env));
			// // parser(tokens);
//Handles Minishell' routine
int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*msh_g;
	t_token		*tokens_tmp;

	(void)argc;
	(void)argv;
	msh_g = g_getset(&(t_minishell){0});
	msh_g->var_env = env;
	while (1)
	{
		msh_g->tokens = NULL;
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(PROMPT_NAME, ADD_HISTORY);
		msh_g->state = MSH_TOKENIZING;
		msh_g->tokens = tokenize(msh_g->input, msh_g->tokens);
		handle_heredocs(msh_g->tokens);
		ft_lstiter(msh_g->tokens, &expand_token);
		ft_lstiter(msh_g->tokens, &lst_put);
		msh_g->state = MSH_EXECUTING;
		tokens_tmp = msh_g->tokens;
		// msh_g->cmd_table = parse_tokens(&tokens, NULL);
		//print_ast(msh_g->cmd_table);
		//refresh the ast
		msh_g->state = MSH_EXECUTING;
		ft_lstclear(&tokens_tmp, free_token_value);
	}
	return (0);
}
