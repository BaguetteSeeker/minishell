/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/05 22:32:39 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define VALID_PROMPT 1
#define INVLID_PROMPT 0

char	*strip_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr("\"\'", str[i]))
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*open_heredoc(char *input)
{
	char	*tmp;

	tmp = input;
	input = ft_strjoin(input, open_prompt(PS2, NO_HISTORY));
	add_history(input);
	free(tmp);
	return (input);
}

char	*new_heredoc(char *delimiter, bool apd_newline)
{
	char	*doc;
	char	*line;
	char	*tmp;

	doc = ft_strdup("");
	while (1)
	{
		line = open_prompt(PS2, NO_HISTORY);
		if (ft_strcmp(line, delimiter))
		{
			tmp = doc;
			if (apd_newline)
				doc = ft_strjoin2(doc, line, "\n");
			else
				doc = ft_strjoin(doc, line);
			free(tmp);
			free(line);
			if (!doc)
				put_err("Failled to alloc memory");
			add_history(doc);
		}
		else
			return (doc);
	}
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
			hereline = new_heredoc(here_start, true);
			free(token->next->value);
			token->next->value = hereline;
		}
		token = token->next;
	}
}
