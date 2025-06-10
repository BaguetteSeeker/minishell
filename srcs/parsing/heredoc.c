/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:27:43 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/10 00:53:35 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_heredoc_eof(char *clean_delimiter)
{
	if (g_getset(NULL)->signal == SIGINT)
		return ;
	ft_putstr_fd("msh: warning: heredoc delimited by EOF", STDERR_FILENO);
	ft_dprintf(STDERR_FILENO, " (expected `%s')\n", clean_delimiter);
}

static char	*new_heredoc(char *delimiter, char *doc, bool apd_newline)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = wait_line(STDIN_FILENO, get_var_value(VAR_SHELL, "PS2"));
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
			return (free(line), doc);
	}
}

//Stamps a DEL (char 127) character right between the heredoc' end
//and the EOF character to mark the heredoc as "expandable"
static char	*stamp_xpd_proc(char *content, char *dltr)
{
	char	*stamped_hdc;
	size_t	content_len;

	if (!ft_strchr(dltr, CHR_DQTE) && !ft_strchr(dltr, CHR_SQTE))
	{
		content_len = ft_strlen(content);
		stamped_hdc = ft_realloc(content, content_len + 2, content_len);
		if (!stamped_hdc)
			put_err("Heredoc processing : realloc faillure");
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

	g_getset(NULL)->state = MSH_HEREDOC;
	doc = ft_strdup("");
	delimiter = token->next->value;
	delimiter_copy = chkalloc(ft_strdup(delimiter), "HRDC: dup fail");
	doc = new_heredoc(strstripchr(delimiter_copy, QUOTES_SET,
				ft_strlen(delimiter_copy)), doc, true);
	free(delimiter_copy);
	doc = stamp_xpd_proc(doc, delimiter);
	token->next->value = doc;
	free(delimiter);
}
