/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/04 19:44:26 by epinaud          ###   ########.fr       */
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

char	*open_heredoc(char *input)
{
	char	*tmp;

	tmp = input;
	input = ft_strjoin(input, open_prompt(PS2));
	add_history(input);
	free(tmp);
	return (input);
}

char	*new_heredoc(char *delimiter)
{
	char	*input;
	char	*content;

	content = NULL;
	while (1)
	{
		input = open_prompt(PS2);
		if (!ft_strrnstr(input, delimiter, ft_strlen(delimiter))
			|| ft_strlen(delimiter) != ft_strlen(input))
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
			hereline = realloc(hereline, sizeof(char) * (ft_strlen(hereline) + 2));
			hereline[ft_strlen(hereline) + 1] = '\0';
			hereline[ft_strlen(hereline)] = '\n';
			free(token->next->value);
			token->next->value = hereline;
		}
		token = token->next;
	}
}
