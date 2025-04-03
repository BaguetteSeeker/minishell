/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/04 01:04:23 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_value(t_token *token)
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

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("token node str is empty", 1));
	ft_putstr_fd("Stack member has token : ", 1);
	ft_putstr_fd(lst->value, 1);
	ft_printf(" of type %d\n", lst->type);
}

void	put_err(char *msg)
{
	if (*msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	//get allocated objects & clean em
	exit(EXIT_FAILURE);
}
