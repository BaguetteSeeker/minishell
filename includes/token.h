/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/06/10 17:12:40 by epinaud          ###   ########.fr       */
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

# define TOKEN_DELIMITORS "><|()& \t\r\n\v\f"
# define OP_CHARSET "><|()&"
# define OP_RECORD 7
# define SEP_CHARSET " \t\r\n\v\f"

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	size_t			type;
}	t_token;

typedef enum quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote;

typedef struct s_segment
{
	char	*text;
	t_quote	quote;
	int		from_var;
}	t_segment;

typedef struct s_word
{
	char			*text;
	int				index;
	int				should_split;
	int				from_variable;
	struct s_word	*previous;
	struct s_word	*next;
	t_segment		**seg;
}	t_word;

#endif
