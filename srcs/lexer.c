/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/21 17:08:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_value(t_token *token)
{
	static int	to_clean[] = {
		PIPE,
		AMPERSAND,
		OR_IF,
		AND_IF,
		LESS,
		GREAT,
		DLESS,
		DGREAT,
		OPAR,
		CPAR
	};

	if (in_array(token->type, to_clean, sizeof(to_clean) / sizeof(int)))
		free(token->value);
}

void	clean_minishell(t_token **token_lst)
{
	//get main object thgough getsetter
	ft_lstclear(token_lst, &free_token_value);
}

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("token node str is empty", 1));
	ft_putstr_fd("Stack member has token : ", 1);
	ft_putstr_fd(lst->value, 1);
	ft_printf(" of type %d\n", lst->type);
}

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

size_t	create_token(char *prompt, t_token *token)
{
	size_t	offset;

	offset = 0;
	if (ft_strchr(OP_CHARSET, prompt[offset]))
	{
		*token = get_grammar_token(prompt);
		if (token->type)
			offset += ft_strlen(token->value);
	}
	else
	{
		while (!ft_strchr("><|& ", prompt[offset]))
		{
			if (ft_strchr("\"\'", prompt[offset])
				&& ft_strchr(&prompt[offset + 1], prompt[offset]))
				offset += ft_strchr(&prompt[offset + 1], prompt[offset]) - &prompt[offset];
			offset++;
		}
		token->type = WORD;
	}
	token->value = ft_substr(prompt, 0, offset);
	if (!token->value)
		exit(1);
	return (offset);
}

#define INVALID_SYNTAX 0
#define VALID_SYNTAX 1
#define ERR_MSG_SYNTAX "syntax error near unexpected token `"

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
				&& tokens->next->type != WORD))
			return (ft_dprintf(STDERR_FILENO, "%s %s%s\'\n",
					PROMPT_NAME, ERR_MSG_SYNTAX, tokens->next->value));
		tokens = tokens->next;
	}
	return (VALID_SYNTAX);
}

t_token	*lexer(char *prompt)
{
	t_token	*token_head;
	t_token	*token;

	token = NULL;
	token_head = token;
	while (*prompt)
	{
		while (ft_strchr(" \t\v\n", *prompt))
			prompt++;
		token = ft_lstnew(&(t_token){0});
		// if !token
		prompt += create_token(prompt, token);
		// ft_printf("Returned token type is %u and content is %s next with %p ptr\\n\n", 
		// 	token->type, token->value, token->next);
		ft_lstadd_back(&token_head, token);
	}
	if (token)
		ft_lstiter(token_head, &lst_put);
	check_syntax(token_head);
	return (token_head);
}
