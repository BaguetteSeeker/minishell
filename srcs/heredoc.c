/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/04 00:56:46 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr("\n", str[i]))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

// char	*new_hereline(char *input)
// {
// 	char	*tmp;

// 	if (input)
// 	{
// 		tmp = input;
// 		input = ft_strjoin(input, open_prompt(PS2));
// 		add_history(input);
// 		free(tmp);
// 	}
// 	else
// 		input = open_prompt(PS2);
// 	return (input);
// }

char	*new_heredoc(char *delimiter)
{
	char	*input;
	char	*content;

	content = NULL;
	while (1)
	{
		input = open_prompt(PS2);
		if (!ft_strrnstr(input, delimiter, ft_strlen(delimiter)))
		{
			if (!content)
				content = ft_strdup("");
			content = ft_strjoin(content, input);
			if (!content)
				put_err("Failled to alloc memory");
			add_history(content);
			free(input);
		}
		else
			break ;
	}
	return (content);
}

void	handle_heredocs(t_token *token)
{
	char	*hereline;
	char	*here_start;

	while (token && token->next)
	{
		if (token->type == DLESS && token->next->type == WORD)
		{
			here_start = strip_quotes(token->next->value);
			hereline = new_heredoc(here_start);
			free(token->next->value);
			token->next->value = hereline;
		}
		token = token->next;
	}
}
