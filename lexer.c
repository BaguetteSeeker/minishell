/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/02/21 18:31:50 by epinaud          ###   ########.fr       */
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
	token->type = type;
	token->value = value;
	ft_printf("Token type is %u and content is %s\nReturning offset %u\n", token->type, token->value, offset);
	return (offset);
}

//ft_printf("Occ of frnl within <Hello friends>is at %s\n", ft_strocc("Hello friends", "frl"));
t_token	**lexer(char *prompt)
{
	t_token	**token_lst;
	t_token	*token;

	token_lst = NULL;
	token = NULL;
	while (*prompt)
	{
		while (ft_strchr(" \t\v\n", *prompt))
			prompt++;
		if (*prompt)
		{
			token = ft_lstnew(&(t_token){0});
			prompt += create_token(prompt, token);
			ft_printf("Returned token type is %u and content is %s\n\n", token->type, token->value);

		}
		ft_lstadd_back(token_lst, token);
	}
	if (token)
		ft_lstiter(*token_lst, &lst_put);
	return (token_lst);
}
