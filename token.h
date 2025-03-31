/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/03/31 13:36:15 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stddef.h>
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
 * @IO_NUMBER: Any number following a redirection
 * @OPAR: (
 * @CPAR: )
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
	OPAR,
	CPAR,
	NEWLINE,
	IO_NUMBER
};

# define OP_CHARSET "><|&()"
# define OP_RECORD 7
# define SEP_CHARSET " \t\r\n\v\f"

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