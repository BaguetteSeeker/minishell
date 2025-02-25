/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/02/25 16:11:45 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("token node str is empty", 1));
	ft_putstr_fd("Stack member has member : ", 1);
	ft_putendl_fd(lst->value, 1);
	free(lst->value);
}

size_t	offset_token(char *prompt)
{
	size_t	offset;


	return (offset);
}

size_t	create_token(char *prompt, t_token *token)
{
	char	*value;
	size_t	offset;
	int		dquote;
	int		squote;

	offset = ft_strocc(prompt, " \t\r\n\v\f\0") - prompt;
	//operator
	if (ft_strchr("><|&", prompt[offset]) && !dquote && !squote)
	{
		type = prompt[offset];
		//double operator
		if (ft_strchr("><|&", prompt[1]))
			type = type * 100 + type;
	}
	else if (ft_strchr("\"\'", prompt[offset]))
	{
		if (prompt[offset] == '\"' && dquote)
			dquote = 0;
		else if (prompt[offset] == '\'' && dquote)
			squote = 0;
		offset++;
	}
	else if (prompt[offset] == ' ' && !dquote && !squote)
	{
		token->type = WORD;
		token->value = ft_substr(prompt, 0, offset);
		//offset value
	}
	//if !value
	/* part of WORD
		else if (ft_strchr("$-\'\"", *prompt))`
		type = *prompt;
	*/	
	value = ft_substr(prompt, 0, offset);
	if (!value)
		exit(1);
	token->value = value;
	ft_printf("Token type is %u and content is %s next with %p ptr\nReturning offset %u\n", token->type, token->value, token->next, offset);
	return (offset);
}

//ft_printf("Occ of frnl within <Hello friends>is at %s\n", ft_strocc("Hello friends", "frl"));
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
		if (*prompt)
		{
			token = ft_lstnew(&(t_token){0, NULL, NULL});
			prompt += create_token(prompt, token);
			ft_printf("Returned token type is %u and content is %s next with %p ptr\\n\n", 
				token->type, token->value, token->next);
			ft_lstadd_back(&token_head, token);
		}
	}
	ft_printf("Getting ready to showlist with first token as %p\n", token_head);
	if (token)
		ft_lstiter(token_head, &lst_put);
	return (token_head);
}
