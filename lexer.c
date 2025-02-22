/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/02/22 22:51:30 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "minishell.h"

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("token node str is empty", 1));
	ft_putstr_fd("Stack member has member : ", 1);
	ft_putendl_fd(lst->value, 1);
	free(lst->value);
}

size_t	create_token(char *prompt, t_token *token)
{
	size_t	type;
	char	*value;
	size_t	offset;

	offset = ft_strocc(prompt, " \t\v\n\0") - prompt;
	if (ft_strchr("><|&\'\"", *prompt))
	{
		type = *prompt;
		if (ft_strchr("><|&\'\"", prompt[1]))
			type = type * 100 + type;
	}
	else if (ft_strchr("$-", *prompt))
		type = *prompt;
	else
		type = 'X';
	value = ft_substr(prompt, 0, offset);
	if (!value)
		exit(1);
	token->type = type;
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
