/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:28:11 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/19 14:42:40 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CMD_TABLE_H
# define CMD_TABLE_H
# include "minishell.h"

typedef enum e_node_type {
    NODE_COMMAND,    // Represents a command (e.g., "echo 1")
    NODE_OPERATOR,   // Represents an operator (e.g., "&&")
    NODE_PIPE,
    NODE_SUBSHELL,    // Represents a subshell (e.g., "(...)")
	NODE_REDIRECTION
} t_node_type;

typedef enum e_redir_type {
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
} t_redir_type;

typedef struct  t_redirs
{
	t_redir_type	type;
	char			*file;
	char			*content;
	struct s_redirs	*next;
   
}  t_redirs;

typedef struct s_ast_node {
    t_node_type         type;    // Type of the node (command, operator, subshell)
    char              	*value;  // Value of the node (e.g., command name, operator)
	char              	**args;   // Value of the node (e.g., command name, operator)
	t_redirs  			io_streams;
    struct s_ast_node 	*left;   // Left child (e.g., left operand of an operator)
    struct s_ast_node 	*right;  // Right child (e.g., right operand of an operator)
}	t_ast_node;
#endif
