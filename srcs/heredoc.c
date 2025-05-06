/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/06 18:58:29 by epinaud          ###   ########.fr       */
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

static char	*new_heredoc(char *delimiter, bool apd_newline)
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

//Stamps a DEL (int 127) character right between the heredoc' end
//and the EOF character to mark the heredoc as "expandable"
static char	*stamp_xpd_proc(char *content, char *dltr)
{
	char	*stamped_hdc;
	size_t	content_len;

	if (!ft_strchr(dltr, CHR_DQUOTE) && !ft_strchr(dltr, CHR_SQUOTE))
	{
		content_len = ft_strlen(content);
		stamped_hdc = ft_realloc(content, content_len + 2);
		if (!stamped_hdc)
			put_err("Heredoc processing : realloc fail");
		*(stamped_hdc + content_len) = EXPANDABLE_HEREDOC;
		*(stamped_hdc + content_len + 1) = '\0';
		content = stamped_hdc;
	}
	return (content);
}

void	handle_heredocs(t_token *token)
{
	char	*hereline;
	char	*delimiter;
	char	*delimiter_copy;

	while (token && token->next)
	{
		if (token->type == DLESS && token->next->type == WORD)
		{
			delimiter = token->next->value;
			delimiter_copy = chkalloc(ft_strdup(delimiter), "DLTR_CPY");
			hereline = new_heredoc(strip_quotes(delimiter_copy), true);
			free(delimiter_copy);
			hereline = stamp_xpd_proc(hereline, delimiter);
			token->next->value = hereline;
			free(delimiter);
		}
		token = token->next;
	}
}
