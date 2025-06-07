/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/05/12 23:26:07 by epinaud          ###   ########.fr       */
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

typedef enum { 
	QUOTE_NONE, 
	QUOTE_SINGLE, 
	QUOTE_DOUBLE 
}	quote_t;

//smaller struct used in an array to analyse each word
//only used in exp_varexp.c and its helper
typedef struct s_segment
{
	char	*text;
	quote_t	quote;
	int		from_var;
}	t_segment;

//example were from_variable is useful
//VAR=*
//echo $VAR
//file1 file2
//echo "$VAR"
//*
//(only relevant for wildcard in minishell)
typedef struct s_word
{
	char		*text;			// raw text (partial word)
	int			index;			// index in list (for debugging)
	int			should_split;	// "$VAR $VAR" shouldn't be split, even though it's two words, but $ARG as $ARG="oui oui" should
	int			from_variable;	// indicate if value was from variable
	struct		s_word *previous;
	struct		s_word *next;
	t_segment	**seg;
}	t_word;

#endif