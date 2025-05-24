/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:06:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/12 13:07:32 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_prompt(char *prompt, bool history)
{
	char	*input_line;

	input_line = readline(prompt);
	if (input_line == NULL)
	{
		if (g_getset(NULL)->state == MSH_BLOCKING_PROMPT)
			return (NULL);
		else
			return (exit_shell(EXIT_MSG, 0), NULL);
	}
	else if (history == ADD_HISTORY && *input_line)
		add_history(input_line);
	return (input_line);
}

//if (g_getset(NULL)->state == MSH_HRDC_PROMPTING)