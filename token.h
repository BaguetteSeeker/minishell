/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/02/24 17:30:57 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdarg.h>
/**
 * enum Token_Types - Types of tokens in a command line
 * @WORD: A word in the command line
 * @DQUODE: " 
 * @SQUOTE: ' 
 * @PIPE: |
 * @AMPERSAND: &
 * @OR_IF: ||
 * @AND_IF: &&
 * @LESS: <
 * @GREAT: >
 * @DLESS: <<
 * @DGREAT: >>
 * @IO_NUMBER: 
 * @OPAR:
 * @CPAR:
 * @DOLLAR: $
 * @WILDCARD: *
 */
enum	e_Token_Types
{
	WORD,
	PIPE,
	AMPERSAND,
	OR_IF,
	AND_IF,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	IO_NUMBER
};

/***************************************************************************
 * 
 * type : type of the token [enum type]
 * str : string of the token, with no leading or trailing spaces
 * args : array of strings, 
 *      each string is an argument (or option) of the token
 * next : pointer to the next token in the list
 * prev : pointer to the previous token in the list
 *  TODO: prev not managed so far.
 * 	NOTE: args is better managed during the AST buildup,
 * 			once tokenization has been made
 * 
 ***************************************************************************/

typedef struct s_token
{
	size_t			type;
	char			*value;
	struct s_token	*next;
}	t_token;


#endif