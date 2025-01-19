/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tokens_so.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/01/19 01:54:44 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TOKENS_SO_H
# define STRUCT_TOKENS_SO_H

/***************************************************************************
 * 
 * type : type of the token [enum type]
 * str : string of the token, with no leading or trailing spaces
 * args : array of strings, 
 *      each string is an argument (or option) of the token
 * next : pointer to the next token in the list
 * prev : pointer to the previous token in the list
 *  TODO: prev not managed so far.
 * 
 ***************************************************************************/
typedef struct s_token
{
	int				type;
	char			*str;
	char			**args;
	struct s_token	*next;
}					t_token;

#endif