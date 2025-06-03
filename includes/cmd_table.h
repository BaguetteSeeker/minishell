/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:28:11 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 13:31:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TABLE_H
# define CMD_TABLE_H
# include "minishell.h"

typedef enum e_node_type
{
	NODE_COMMAND,	// Represents a command (e.g., "echo 1")
	NODE_OPERATOR,	// Represents an operator (e.g., "&&")
	NODE_PIPE,	// Represents one or more contiguous pipes ("cmd1|cmd2|cmd3...")
	NODE_SUBSHELL,	// Represents a subshell (e.g., "(...)")
}	t_node_type;

//je mets ca la pour l'instant
//tu peux le bouger dans un "built-ins.h ou autre part stv
typedef enum e_bi_type
{
	BUILTIN_NONE = -1,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_bi_type;

typedef enum e_redir_type
{
	REDIR_IN = LESS,
	REDIR_OUT = GREAT,
	HEREDOC = DLESS,
	APPEND = DGREAT
}	t_redir_type;

typedef struct s_redir
{
	char			*file;
	char			*exp_file;
	struct s_redir	*next;
	t_redir_type	type;
}	t_redir;

typedef struct s_ast_node
{
	t_node_type			type;	// Type of the node
	int					is_foreground; // Flag
	char				*value;	// Value of the node (command name, operator)
	char				**args;	// Command' arguments, comes from lexer DO NOT FREE
	char				**exp_args;	// command's arguments post expansion
	char				**vars;	// Temporary command vars OR shell vars
	char				**exp_vars;	// same thing as exp_args
	t_redir				*io_streams; // Linked List of redirections
	struct s_ast_node	*left;	// Left child (operator' left node)
	struct s_ast_node	*right;	// Right child (operator' right node)
}	t_ast_node;
#endif
