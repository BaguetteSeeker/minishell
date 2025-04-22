/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_typ.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:04 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/22 16:57:56 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LL_TYP_H
# define LL_TYP_H
# define LL_TYP t_token
# define lstadd_back_redirs(list_head, new_list) \
	ft_lstadd_back((LL_TYP **)(list_head), (LL_TYP *)(new_list))
# define lstnew_redirs(content) ft_lstnew((void *)(content))
# define lstiter_redirs(lst, f) ft_lstiter((t_token *)(lst), f)
# include "token.h"
#endif