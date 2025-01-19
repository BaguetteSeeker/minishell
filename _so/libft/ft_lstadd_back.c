/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:05:22 by souaret           #+#    #+#             */
/*   Updated: 2024/05/28 19:38:18 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*i_lst;

	i_lst = *lst;
	if (i_lst == 0)
	{
		*lst = new;
	}
	else
	{
		while (i_lst != 0)
		{
			if (i_lst->next == 0)
			{
				i_lst->next = new;
				return ;
			}
			else
			{
				i_lst = i_lst->next;
			}
		}
	}
}
