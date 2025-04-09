/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/09 18:27:23 by epinaud          ###   ########.fr       */
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
		return (i);
	}
	else
	{
		while (input[i] && !ft_strchr("><|&() ", input[i]))
		{
			if (ft_strchr(QUOTES_SET, input[i])
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

void	check_completion(t_token *token, t_token *head)
{
	static int	par_dft = 0;

	if (token->type == OPAR)
		par_dft++;
	else if (token->type == CPAR)
		par_dft--;
	if (par_dft < 0)
		return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n", PROMPT_NAME,
				ERR_MSG_SYNTAX, token->value), exit(1));
	if (token->next->type == T_NEWLINE && (par_dft > 0
			|| token->type == OR_IF || token->type == AND_IF
			|| token->type == PIPE))
		tokenize(open_prompt(PS2), head);
}

int	check_syntax(t_token *tok, t_token *head)
{
	static int	op_tok[] = {LESS, DLESS, GREAT, DGREAT, PIPE, OR_IF, AND_IF};
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};

	if (tok && tok->next)
	{
		if ((in_array(tok->type, op_tok, sizeof(op_tok) / sizeof(int)) > -1
				&& in_array(tok->next->type, op_tok,
					sizeof(op_tok) / sizeof(int)) > -1)
			|| (in_array(tok->type, redirs,
					sizeof(redirs) / sizeof(int)) > -1
				&& tok->next->type != WORD)
			|| (tok->type == DLESS && tok->next->type != WORD)
			|| (tok->type == CPAR && tok->next->type == OPAR))
			return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n", PROMPT_NAME,
					ERR_MSG_SYNTAX, tok->next->value), exit(1), INVALID_SYNTAX);
		check_completion(tok, head);
	}
	return (VALID_SYNTAX);
}

t_token	*tokenize(char *prompt, t_token *token_head)
{
	t_token	*token;
	t_token	*prev_token;
	char	*tmp;

	tmp = prompt;
	token = NULL;
	while (1)
	{
		while (*prompt && ft_strchr(SEP_CHARSET, *prompt))
			prompt++;
		token = ft_lstnew(&(t_token){0});
		if (!token)
			put_err("Failled to allocate memory for tokens");
		if (!*prompt)
			*token = (t_token){T_NEWLINE, "newline", NULL};
		else
			prompt += create_token(prompt, token);
		prev_token = ft_lstlast(token_head);
		ft_lstadd_back(&token_head, token);
		check_syntax(prev_token, token_head);
		if (token->type == T_NEWLINE)
			break ;
	}
	free(tmp);
	return (token_head);
}
