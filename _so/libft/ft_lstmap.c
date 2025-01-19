/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:28:09 by souaret           #+#    #+#             */
/*   Updated: 2024/05/31 17:09:29 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
35			ft_lstclear(&first, del);

43			// del(new_content);
44			// ft_lstclear(&first, del);
45			// return (NULL);
*/
static t_list	*ft_clear_up(t_list *first, void *new_c, void (*del)(void *))
{
	del(new_c);
	ft_lstclear(&first, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;
	void	*new_c;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new_c = (*f)(lst->content);
		if (!new_c)
		{
			return (ft_clear_up(first, new_c, del));
		}
		new = ft_lstnew(new_c);
		if (new == NULL)
		{
			return (ft_clear_up(first, new_c, del));
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
