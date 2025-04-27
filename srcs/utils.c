/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/27 00:55:06 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_value(t_token *token)
{
	static int	no_clean[] = {
		PIPE,
		AMPERSAND,
		OR_IF,
		AND_IF,
		LESS,
		GREAT,
		DLESS,
		DGREAT,
		OPAR,
		CPAR,
		T_NEWLINE
	};

	if (in_array(token->type, no_clean, sizeof(no_clean) / sizeof(int)) == -1)
		free(token->value);
}

void	clean_shell(void)
{
	ft_lstclear(&g_getset(NULL)->tok_lst, free_token_value);
}

void	lst_put(t_token *lst)
{
	if (!lst)
		return (ft_putendl_fd("Node does not exist", 1));
	ft_putstr_fd("Node content > : ", 1);
	ft_putstr_fd(lst->value, 1);
	ft_printf(" of type %d\n", lst->type);
}

void	put_err(char *msg)
{
	if (*msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	//call for shell cleaning
	exit(EXIT_FAILURE);
}
