/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/12 23:14:40 by epinaud          ###   ########.fr       */
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

static void	put_heredoc_eof(char *clean_delimiter)
{
	ft_putstr_fd("msh: warning: heredoc delimited by EOF", STDERR_FILENO);
	ft_dprintf(STDERR_FILENO, " (expected `%s')\n", clean_delimiter);
}

static char	*new_heredoc(char *delimiter, char *doc, bool apd_newline)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = open_prompt(PS2, NO_HISTORY);
		if (!line)
			return (put_heredoc_eof(delimiter), doc);
		else if (ft_strcmp(line, delimiter))
		{
			tmp = doc;
			if (apd_newline)
				doc = ft_strjoin2(doc, line, "\n");
			else
				doc = ft_strjoin(doc, line);
			free(tmp);
			free(line);
			if (!doc)
				put_err("Heredoc processing: malloc faillure");
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

void	handle_heredoc(t_token *token)
{
	char	*doc;
	char	*delimiter;
	char	*delimiter_copy;

	g_getset(NULL)->state = MSH_HRDC_PROMPTING;
	doc = ft_strdup("");
	delimiter = token->next->value;
	delimiter_copy = chkalloc(ft_strdup(delimiter), "HRDC: dup fail");
	doc = new_heredoc(strip_quotes(delimiter_copy), doc, true);
	free(delimiter_copy);
	doc = stamp_xpd_proc(doc, delimiter);
	token->next->value = doc;
	free(delimiter);
}
