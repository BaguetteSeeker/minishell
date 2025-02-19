/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/02/19 20:28:15 by epinaud          ###   ########.fr       */
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

	ft_printf("Enter strings (empty input to exit):\n");
	while (1) 
	{
		// ft_printf("$minishell:");
		input_line = readline("$minishell:");
		if (input_line == NULL || *input_line == '\0') 
		{
			free(input_line);
			break ;
		}
		add_history(input_line);
		//ft_printf("==> %s\n", input_line);
		free(input_line);
	}
	return (0);
}
