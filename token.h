/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/01/29 19:09:56 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
# define LL_TYP t_token

typedef struct s_token
{
	int				type;
	char			*str;
	char			**args;
	struct s_token	*next;
}	t_token;

#endif