/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/08 00:02:29 by epinaud          ###   ########.fr       */
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

//Finalize err response
int	check_syntax(t_token *tokens, t_token *head)
{
	(void)head;
	static int	redirs[] = {LESS, DLESS, GREAT, DGREAT};
	static int	cmdsep[] = {PIPE, OR_IF, AND_IF};
	static int	par_depth = 0;
	
	if (tokens && tokens->next)
	{
		if (tokens->type == OPAR)
			par_depth++;
		else if (tokens->type == CPAR)
			par_depth--;
		if ((in_array(tokens->type, cmdsep, sizeof(cmdsep) / sizeof(int)) > -1
				&& in_array(tokens->next->type, cmdsep,
					sizeof(cmdsep) / sizeof(int)) > -1)
			|| (in_array(tokens->type, redirs,
					sizeof(redirs) / sizeof(int)) > -1
				&& tokens->next->type != WORD)
			|| (tokens->type == DLESS && tokens->next->type != WORD)
			|| (par_depth < 0))
			return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n",
					PROMPT_NAME, ERR_MSG_SYNTAX, tokens->next->value));
		tokens = tokens->next;
	}
	/* if (tokens->type == NEWLINE && par_depth > 0)
	{
		ft_lstdelone(token->next);
		new_heredoc();
	}
	*/
	//Trigger error for bash-5.0$ (heyy; (((ohh)) && (jj
	//Trigger error for WORD preceeding OPAR
	// if (par_depth > 0)
	// 	ft_dprintf(STDERR_FILENO, "%s %s%s\'\n",
	// 		PROMPT_NAME, ERR_MSG_SYNTAX, tokens->next->value);
	return (VALID_SYNTAX);
}

t_token	*tokenize(char *prompt, t_token *token_head)
{
	t_token	*token;
	t_token	*prev_token;

	token = NULL;
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
		prev_token = ft_lstlast(token_head);
		ft_lstadd_back(&token_head, token);
		check_syntax(prev_token, token_head);
	}
	token = ft_lstnew(&(t_token){NEWLINE, "newline", NULL});
	ft_lstadd_back(&token_head, token);
	// if (token)
	// {
	// 	// ft_lstiter(token_head, &lst_put);
		
	// }
	return (token_head);
}
