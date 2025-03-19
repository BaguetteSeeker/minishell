/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/19 23:27:16 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define INVALID_SYNTAX 0
#define VALID_SYNTAX 1
#define ERR_MSG_SYNTAX "syntax error near unexpected token `"
#define PROMPT_NAME "$minishell:"

int	parser(t_token *tokens)
{
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};
	static int	forks[] = {PIPE, OR_IF, AND_IF};

	while (tokens->next)
	{
		if ((in_array(tokens->type, forks, sizeof(forks) / sizeof(int)) > -1
				&& in_array(tokens->next->type, forks,
					sizeof(forks) / sizeof(int)) > -1)
			|| (in_array(tokens->type, redirs,
					sizeof(redirs) / sizeof(int)) > -1
				&& tokens->next->type != WORD))
			return (ft_dprintf(STDERR_FILENO, "%s %s %s\n",
					PROMPT_NAME, ERR_MSG_SYNTAX, tokens->next->value));
		tokens = tokens->next;
	}
	return (VALID_SYNTAX);
}
