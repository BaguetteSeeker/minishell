/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/03/31 22:22:58 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define VALID_PROMPT 1
# define INVLID_PROMPT 0

t_minishell	*getset_env(void *g)
{
	static t_minishell *stored_g = {NULL};

	if (!stored_g)
		stored_g = g;
	return (stored_g);
}

//Add skip quotes function
// int	skip_quotes;

//Check the following characters for open and closure [\"\'(]

// size_t	offset_quotes(char *str)
// {
// 	size_t	offset;

// 	offset
// }

int	check_line(char *input)
{
	int	missing_par;

	missing_par = 0;
	while (*input)
	{
		if (*input == '(')
			missing_par++;
		else if (*input == ')')
			missing_par--;
		else if (ft_strchr(QUOTES_SET, *input) && ft_strchr(input + 1, *input))
		{
			input += (long)ft_strchr(input + 1, *input) - (long)input;
			continue ;
		}
		// if (missing_par < 0) //Apparently managed during token syntax check
		// 	return (INVLID_PROMPT);
		input++;
	}
	if (!missing_par)
		return (VALID_PROMPT);
	else
		return (INVLID_PROMPT);
}

char	*open_prompt(char *prompt)
{
	char	*input_line;

	input_line = readline(prompt);
	if (input_line == NULL /* || *input_line == '\0' */) 
		return (free(input_line), NULL);
	return (input_line);
}

char	*open_heredoc(char *input)
{
	char	*tmp;

	tmp = input;
	input = ft_strjoin(input, open_prompt(PS2));
	add_history(input);
	free(tmp);
	return (input);
}

int	main(int argc, char *argv[], char *env[]) 
{
	(void)argc;
	(void)argv;
	char	*input_line;
	t_token	*tokens;
	(void)tokens;

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
		// handle_heredocs(input_line, tokens);
		while (!check_line(input_line))
			input_line = open_heredoc(input_line);
		// // parser(tokens);
		free(input_line);
	}
	return (0);
}
