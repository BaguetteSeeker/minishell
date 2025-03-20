/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/03/20 18:04:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void) 
{
	char	*input_line;
	//t_token	*tokens;

	while (1) 
	{
		input_line = readline(PROMPT_NAME);
		if (input_line == NULL || *input_line == '\0') 
		{
			free(input_line);
			break ;
		}
		add_history(input_line);
		/* tokens =  */lexer(input_line);
		// parser(tokens);
		free(input_line);
	}
	return (0);
}
