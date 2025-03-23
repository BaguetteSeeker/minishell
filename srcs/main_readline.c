/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/03/23 21:23:55 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define VALID_PROMPT 1
# define INVLID_PROMPT 0

char	getset_env(void *g)
{
	static t_minishell *stored_g = {NULL};

	if (!stored_g)
		stored_g = g;
	return (stored_g);
}

//Add skip quotes function
int	skip_quotes

size_t	check_prompt(char *input)
{
	(void)input;

	//Check the following characters for open and closure [\"\'(]
	return (VALID_PROMPT);
}

void	open_prompt(void)
{
	char	*input_line;
	//t_token	*tokens;

		input_line = readline(PROMPT_NAME);
		if (input_line == NULL || *input_line == '\0') 
			return (free(input_line));
		add_history(input_line);
		/* tokens =  *///lexer(input_line);
		// parser(tokens);
		free(input_line);
}

int	main(int argc, char *argv[], char *env[]) 
{
	getset_env(&(t_minishell){0});
	while (1) 
	{
		open_prompt();
	}
	return (0);
}
