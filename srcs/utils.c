/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/05 22:17:18 by epinaud          ###   ########.fr       */
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
		CPAR
	};

	if (in_array(token->type, no_clean,
			sizeof(no_clean) / sizeof(int)) == -1)
		free(token->value);
}

void	clean_shell(void)
{
	ft_lstclear(&g_getset(NULL)->tokens, free_token_value);
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
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	// cleaner();
	exit(EXIT_FAILURE);
}

void	*chkalloc(char *val, char *msg)
{
	if (!val)
	{
		ft_putendl_fd(ERRMSG_MALLOC_FAIL, STDERR_FILENO);
		put_err(msg);
	}
	return (val);
}
