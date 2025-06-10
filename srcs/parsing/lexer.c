/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/10 16:02:05 by anle-pag         ###   ########.fr       */
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

static size_t	create_token(char *input, t_token *token)
{
	size_t	i;

	i = 0;
	*token = get_grammar_token(input);
	if (token->type != WORD)
		return (ft_strlen(token->value));
	else
	{
		while (input[i] && !ft_strchr(SEP_CHARSET, input[i])
			&& get_grammar_token(input + i).type == WORD)
		{
			if (ft_strchr(QUOTES_SET, input[i])
				&& ft_strchr(&input[i + 1], input[i]))
				i += ft_strchr(&input[i + 1], input[i]) - &input[i];
			i++;
		}
	}
	token->value = chkalloc(ft_substr(input, 0, i), "Lexer: Malloc Faillure");
	return (i);
}

//Keeps a count of parenthesis opened and prompts for completion
//until their closing equivalent is fully registered
//Throws a syntax error in the case of standalone CPAR `)`
static t_token	*check_completion(t_token *token, t_token **head)
{
	static int	par_depth = 0;

	if (token->type == DLESS)
	{
		handle_heredoc(token);
		if (g_getset(NULL)->signal == SIGINT)
			return (par_depth = 0, g_getset(NULL)->state = MSH_FAILLURE, NULL);
	}
	if (token->type == OPAR)
		par_depth++;
	else if (token->type == CPAR)
		par_depth--;
	if (par_depth < 0)
		return (g_getset(NULL)->state = MSH_FAILLURE,
			par_depth = 0, ft_dprintf(STDERR_FILENO, "%s %s%s\'\n",
				SHELL_NAME, ERRMSG_SYNTAX, token->next->value), fflush(stderr), NULL);
	if (token->next->type == T_NEWLINE && (par_depth > 0 || token->type == OR_IF
			|| token->type == AND_IF || token->type == PIPE))
		complete_prompt(token, head, &par_depth);
	return ((t_token *)msh_lstlast(*head));
}

static t_token	*check_syntax(t_token *tok, t_token **head)
{
	static int	oper[] = {PIPE, OR_IF, AND_IF};
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};

	if (tok && tok->next)
	{
		if ((in_array(tok->type, oper, nb_elems(oper, sizeof(oper)))
				&& in_array(tok->next->type, oper,
					nb_elems(oper, sizeof(oper))))
			|| (in_array(tok->type, redirs, nb_elems(redirs, sizeof(redirs)))
				&& tok->next->type != WORD)
			|| (tok->type == DLESS && tok->next->type != WORD)
			|| (tok->type == CPAR && tok->next->type == OPAR)
			|| (tok->type == WORD && tok->next->type == OPAR))
			return (g_getset(NULL)->state = MSH_FAILLURE,
				ft_dprintf(STDERR_FILENO, "%s: %s%s\'\n", SHELL_NAME,
					ERRMSG_SYNTAX, tok->next->value), fflush(stderr), NULL);
		else if (in_array(tok->type, oper, nb_elems(oper, sizeof(oper)))
			&& *head == tok)
			return (g_getset(NULL)->state = MSH_FAILLURE,
				ft_dprintf(STDERR_FILENO, "%s: %s%s\'\n", SHELL_NAME,
					ERRMSG_SYNTAX, tok->value), fflush(stderr), NULL);
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
		prev_token = (t_token *)msh_lstlast(*token_head);
		msh_lstaddback(token_head, token);
		token = check_syntax(prev_token, token_head);
		if (token == NULL || token->type == T_NEWLINE)
			break ;
	}
	return (free(*inpt_ptr), *inpt_ptr = NULL, *token_head);
}
