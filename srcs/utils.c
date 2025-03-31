/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/27 12:46:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clean_minishell(t_token **token_lst)
// {
// 	//get main object through getsetter
// 	ft_lstclear(token_lst, &free_token_value);
// }

void	put_err(char *msg)
{
	if (*msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	//get allocated objects & clean em
	exit(EXIT_FAILURE);
}