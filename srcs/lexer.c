/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/04 01:03:13 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	get_grammar_token(char *input)
{
	static t_token	grammar_tokens[] = {
	{.type = OR_IF, .value = "||"},
	{.type = PIPE, .value = "|"},
	{.type = AND_IF, .value = "&&"},
	{.type = AMPERSAND, .value = "&"},
	{.type = DLESS, .value = "<<"},
	{.type = LESS, .value = "<"},
	{.type = DGREAT, .value = ">>"},
	{.type = GREAT, .value = ">"},
	{.type = OPAR, .value = "("},
	{.type = CPAR, .value = ")"}};
	size_t			i;

	i = 0;
	while (i < sizeof(grammar_tokens) / sizeof(*grammar_tokens))
	{
		if (ft_strncmp(grammar_tokens[i].value, input,
				ft_strlen(grammar_tokens[i].value)) == 0)
			return (grammar_tokens[i]);
		i++;
	}
	return ((t_token){0});
}

size_t	create_token(char *input, t_token *token)
{
	size_t	i;

	i = 0;
	if (ft_strchr(OP_CHARSET, input[i]))
	{
		*token = get_grammar_token(input);
		if (token->type)
			i += ft_strlen(token->value);
	}
	else
	{
		while (input[i] && !ft_strchr("><|&) ", input[i]))
		{
			if (ft_strchr("\"\'", input[i])
				&& ft_strchr(&input[i + 1], input[i]))
				i += ft_strchr(&input[i + 1], input[i]) - &input[i];
			i++;
		}
		token->type = WORD;
	}
	token->value = ft_substr(input, 0, i);
	if (!token->value)
		exit(1);
	return (i);
}

#define INVALID_SYNTAX 0
#define VALID_SYNTAX 1

//Finalize err response
int	check_syntax(t_token *tokens)
{
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};
	static int	cmdsep[] = {PIPE, OR_IF, AND_IF};

	while (tokens->next)
	{
		if ((in_array(tokens->type, cmdsep, sizeof(cmdsep) / sizeof(int)) > -1
				&& in_array(tokens->next->type, cmdsep,
					sizeof(cmdsep) / sizeof(int)) > -1)
			|| (in_array(tokens->type, redirs,
					sizeof(redirs) / sizeof(int)) > -1
				&& tokens->next->type != WORD)
			|| (tokens->type == DLESS && tokens->next->type != WORD))
			return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n",
					PROMPT_NAME, ERR_MSG_SYNTAX, tokens->next->value));
		tokens = tokens->next;
	}
	return (VALID_SYNTAX);
}

t_token	*tokenize(char *prompt)
{
	t_token	*token_head;
	t_token	*token;

	token = NULL;
	token_head = token;
	while (*prompt)
	{
		while (*prompt && ft_strchr(SEP_CHARSET, *prompt))
			prompt++;
		if (!*prompt)
			break ;
		token = ft_lstnew(&(t_token){0});
		if (!token)
			put_err("Failled to allocate memory for tokens");
		prompt += create_token(prompt, token);
		ft_lstadd_back(&token_head, token);
	}
	token = ft_lstnew(&(t_token){NEWLINE, "newline", NULL});
	ft_lstadd_back(&token_head, token);
	if (token)
	{
		// ft_lstiter(token_head, &lst_put);
		check_syntax(token_head);
	}
	return (token_head);
}
