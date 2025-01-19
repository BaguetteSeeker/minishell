/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:23:41 by souaret           #+#    #+#             */
/*   Updated: 2024/05/28 21:45:25 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*i_lst;

	i_lst = lst;
	if (i_lst == 0)
		return (NULL);
	while (i_lst)
	{
		if (i_lst->next == 0)
			return (i_lst);
		i_lst = i_lst->next;
	}
	return (i_lst);
}
