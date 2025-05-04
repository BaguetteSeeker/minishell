/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/05/04 23:43:59 by epinaud          ###   ########.fr       */
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

char	*open_prompt(char *prompt)
{
	char	*input_line;

	input_line = readline(prompt);
	if (input_line == NULL)
		return (free(input_line), put_err("Readline faillure\n"), NULL);
	return (input_line);
}

// void	expand_node(t_ast_node *node)
// {
// 	node->value = expand(node->value);
// 	node.
// }

// put_recurse_dynarr(g_getset(NULL)->var_env);
// ft_printf("Imported env has %u variables\n",
	// ft_ptrlen((const void **)g_getset(NULL)->var_env));
			// // parser(tokens);
//Handles Minishell' routine
int	main(int argc, char *argv[], char *env[])
{
	char	*input_line;
	t_token	*tokens;
	t_token	*tokens_tmp;

	(void)argc;
	(void)argv;
	g_getset(&(t_minishell){.var_env = env});
 	while (1)
	{
		tokens = NULL;
		g_getset(NULL)->state = MSH_PROMPTING;
		input_line = open_prompt(PROMPT_NAME);
		if (input_line && *input_line)
			add_history(input_line);
		else
			continue ;
		g_getset(NULL)->state = MSH_TOKENIZING;
		tokens = tokenize(input_line, tokens);
		handle_heredocs(tokens);
		tokens_tmp = tokens;
		ft_printf("Prev val %s\nExpanded Val: %s\n", tokens->value, expand(tokens->value));
		g_getset(NULL)->state = MSH_EXECUTING;
		// g_getset(NULL)->cmd_table = parse_tokens(&tokens, NULL);
		//print_ast(g_getset(NULL)->cmd_table);
		// if (tokens)
		// 	ft_lstiter(tokens, &lst_put);
		//refresh the ast
		g_getset(NULL)->state = MSH_EXECUTING;
		ft_lstclear(&tokens_tmp, free_token_value);
	}
	return (0);
}
