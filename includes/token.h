/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/05/12 11:59:17 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/**
 * enum Token_Types - Types of tokens in a command line
 * @WORD: A word in the command line
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
	T_NEWLINE,
	IO_NUMBER
};

# define OP_CHARSET "><|&()"
# define OP_RECORD 7
# define SEP_CHARSET " \t\r\n\v\f"

typedef struct s_token
{
	size_t			type;
	char			*value;
	struct s_token	*next;
}	t_token;

#endif