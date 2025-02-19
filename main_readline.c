/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/02/21 13:33:53 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*********************************************************
 * 
 * To compile & run :
 * 		cc -o main_readline  main_readline.c -lreadline
 * 
 ********************************************************/
int	main(void) 
{
	char	*input_line;

	ft_printf("Enter strings (empty input to exit):\n\n");
	while (1) 
	{
		input_line = readline("$minishell:");
		if (input_line == NULL || *input_line == '\0') 
		{
			free(input_line);
			break ;
		}
		add_history(input_line);
		//ft_printf("==> %s\n", input_line);
		lexer(input_line);
		free(input_line);
	}
	return (0);
}
