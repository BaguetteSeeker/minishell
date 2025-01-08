/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:34:16 by souaret           #+#    #+#             */
/*   Updated: 2025/01/08 20:45:43 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*********************************************************
 * 
 * To compile & run :
 * 		cc -o main_readline  main_readline.c -lreadline
 * 
 ********************************************************/
int	main(void) 
{
	char	*input_line;

	printf("Enter strings (empty input to exit):\n");
	while (1) 
	{
		input_line = readline(NULL);
		if (input_line == NULL || *input_line == '\0') 
		{
			free(input_line);
			break ;
		}
		add_history(input_line);
		printf("==> %s\n", input_line);
		free(input_line);
	}
	return (0);
}
