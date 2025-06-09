/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltype_converts.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 12:15:10 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLTYPE_CONVERTS_H
# define LLTYPE_CONVERTS_H

//Generic MSH Converts
# define msh_lstclear(lst, f) ft_lstclear((t_list **)(lst), (void *)f)
# define msh_lstiter(lst, f) ft_lstiter((t_list *)(lst), (void *)f)
# define msh_lstdelone(lst, f) ft_lstdelone((t_list *)(lst), (void *)f)
# define msh_lstaddback(list_head, new_list) \
	ft_lstadd_back((LL_TYP **)(list_head), (LL_TYP *)(new_list))
# define msh_lstlast(lst) ft_lstlast((t_list *)(lst))
#endif
