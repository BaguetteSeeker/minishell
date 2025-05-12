/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/13 00:01:36 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	get_grammar_token(char *input)
{
	static t_token	grammar_tokens[] = {
	{.type = OR_IF, .value = "||"},
	{.type = PIPE, .value = "|"},
	{.type = AND_IF, .value = "&&"},
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
	if (ft_strchr(OP_CHARSET, input[i])
		&& !(input[i] == '&' && input[i + 1] != '&'))
	{
		*token = get_grammar_token(input);
		if (token->type)
			i += ft_strlen(token->value);
		return (i);
	}
	else
	{
		while (input[i] && (!ft_strchr(TOKEN_DELIMITORS, input[i]
					|| get_grammar_token(input + i).type == WORD)))
		{
			if (ft_strchr(QUOTES_SET, input[i])
				&& ft_strchr(&input[i + 1], input[i]))
				i += ft_strchr(&input[i + 1], input[i]) - &input[i];
			i++;
		}
		token->type = WORD;
	}
	token->value = chkalloc(ft_substr(input, 0, i), "Lexer: Malloc Faillure");
	return (i);
}

//TODO: Craft a printf that returns a concatenated chain instead of printing it
//In order to handle properly the syntax error
t_token	*check_completion(t_token *token, t_token **head)
{
	static int	par_dft = 0;
	char		*input_completion;

	if (token->type == OPAR)
		par_dft++;
	else if (token->type == CPAR)
		par_dft--;
	if (par_dft < 0)
		return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n", PROMPT_NAME,
				ERRMSG_SYNTAX, token->value), put_err(""), token->next);
	if (token->type == DLESS)
		handle_heredoc(token);
	if (token->next->type == T_NEWLINE && (par_dft > 0
			|| token->type == OR_IF || token->type == AND_IF
			|| token->type == PIPE))
	{
		lstdelone_tokens(token->next, free_token_value);
		token->next = NULL;
		input_completion = open_prompt(PS2, NO_HISTORY);
		tokenize(&input_completion, head);
	}
	return ((t_token *)lstlast_tokens(*head));
}

t_token	*check_syntax(t_token *tok, t_token **head)
{
	static int	optok[] = {LESS, DLESS, GREAT, DGREAT, PIPE, OR_IF, AND_IF};
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};

	if (tok && tok->next)
	{
		if ((in_array(tok->type, optok, nb_elems(optok, sizeof(optok)))
				&& in_array(tok->next->type, optok,
					nb_elems(optok, sizeof(optok))))
			|| (in_array(tok->type, redirs, nb_elems(redirs, sizeof(redirs)))
				&& tok->next->type != WORD)
			|| (tok->type == DLESS && tok->next->type != WORD)
			|| (tok->type == CPAR && tok->next->type == OPAR))
			return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n", PROMPT_NAME,
					ERRMSG_SYNTAX, tok->next->value), put_err(""), tok);
		return (check_completion(tok, head));
	}
	return (*head);
}

t_token	*tokenize(char **inpt_ptr, t_token **token_head)
{
	static t_token	*prev_token = NULL;
	t_token			*token;
	char			*input;

	input = *inpt_ptr;
	while (1)
	{
		while (input[0] && ft_strchr(SEP_CHARSET, input[0]))
			input++;
		token = malloc(sizeof(t_token));
		if (!token)
			return (free(*inpt_ptr), inpt_ptr = NULL,
				put_err("Tokenizer: malloc faillure"), NULL);
		*token = (t_token){0};
		if (input[0] == '\0')
			*token = (t_token){chkalloc(ft_strdup("newline"), 0), 0, T_NEWLINE};
		else
			input += create_token(input, token);
		prev_token = (t_token *)lstlast_tokens(*token_head);
		lstadd_back_tokens(token_head, token);
		token = check_syntax(prev_token, token_head);
		if (token->type == T_NEWLINE)
			break ;
	}
	return (free(*inpt_ptr), *inpt_ptr = NULL, *token_head);
}
