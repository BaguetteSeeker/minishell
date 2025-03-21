/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/20 21:49:11 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clean_minishell(t_token **token_lst)
// {
// 	//get main object thgough getsetter
// 	ft_lstclear(token_lst, &free_token_value);
// }

void	put_err(char *msg, int fd)
{
	if (*msg)
		ft_putendl_fd(msg, fd);
	//get allocated objects & clean em
	exit(EXIT_FAILURE);
}