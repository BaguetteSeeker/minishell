/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltype_converts.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/10 17:06:47 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLTYPE_CONVERTS_H
# define LLTYPE_CONVERTS_H

//Generic MSH Converts
# define MSH_LSTCLEAR(lst, f) ft_lstclear((t_list **)(lst), (void *)f)
# define MSH_LSTITER(lst, f) ft_lstiter((t_list *)(lst), (void *)f)
# define MSH_LSTDELONE(lst, f) ft_lstdelone((t_list *)(lst), (void *)f)
# define MSH_LSTADDBACK(l, n) ft_lstadd_back((LL_TYP **)(l), (LL_TYP *)(n))
# define MSH_LSTLAST(lst) ft_lstlast((t_list *)(lst))
#endif
