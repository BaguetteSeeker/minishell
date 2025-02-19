/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:13:42 by epinaud           #+#    #+#             */
/*   Updated: 2025/02/19 20:07:42 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlentill(char *str, char limit)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != limit)
		count++;
	return (count);
}

//Rooting function that passes a pos index of the input to subfunctions that will fill a t_token struct

t_token	*lexer(char *prompt)
{
	t_token	*token;
	(void)prompt;
	//int	i;
	
	char	**items;

	items = ft_split(prompt, ' ');
	while (items)
	{
		items++;
	}

	token = NULL;
	return (token);
}