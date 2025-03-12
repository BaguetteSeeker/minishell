/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/03/11 15:11:57 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void) 
{
	char	*input_line;

	while (1) 
	{
		input_line = readline("$minishell: ");
		if (input_line == NULL || *input_line == '\0') 
		{
			free(input_line);
			break ;
		}
		add_history(input_line);
		lexer(input_line);
		free(input_line);
	}
	return (0);
}
