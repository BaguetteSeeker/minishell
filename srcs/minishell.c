/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/04/04 19:21:53 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	*getset_env(void *g)
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

int	main(int argc, char *argv[], char *env[])
{
	char	*input_line;
	t_token	*tokens;
	(void)argc;
	(void)argv;

	getset_env(&(t_minishell){.var_env = env});
	// recurse_put(getset_env(NULL)->var_env);
	// ft_printf("Imported env has %u variables\n",
		// ft_ptrlen((const void **)getset_env(NULL)->var_env));
	while (1)
	{
		input_line = open_prompt(PROMPT_NAME);
		if (input_line && *input_line)
			add_history(input_line);
		tokens = tokenize(input_line);
		handle_heredocs(tokens);
		if (tokens)
			ft_lstiter(tokens, &lst_put);
		// while (!check_line(input_line))
		// 	input_line = open_heredoc(input_line);
		// // parser(tokens);
		free(input_line);
	}
	return (0);
}
