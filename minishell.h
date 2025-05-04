/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/04 22:58:47 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include <stddef.h>
# include "token.h"
# include "cmd_table.h"
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT_NAME "$minishell:"
# define PS2 "> "
# define ERRMSG_SYNTAX "syntax error near unexpected token `"
# define QUOTES_SET "\"\'"

typedef enum s_msh_state
{
	MSH_PROMPTING,
	MSH_TOKENIZING,
	MSH_PARSING,
	MSH_EXECUTING
}	t_msh_state;

typedef struct s_minishell
{
	t_msh_state state;
	char 		**var_env;
	char		**var_shell;
	char		*prompt;
	t_token		*tok_lst;
	t_ast_node	*cmd_table;
}	t_minishell;

//Functions' Flags
#define	PARSE_SUBSQ_WORDS 1
#define	PARSE_SUBSQ_VARS 2
#define TYPE_DLRS 1
#define TYPE_WCRD 2
#define CHR_SQUOTE '\''
#define CHR_DQUOTE '\"'

//Core
t_minishell	*g_getset(void *g);
t_token		*tokenize(char *prompt, t_token *token_head);
char		*open_prompt(char *prompt);
void		handle_heredocs(t_token *token);
char		*new_heredoc(char *delimiter, bool apd_newline);
void		free_token_value(t_token *token);
t_ast_node	*parse_tokens(t_token **tokens, t_ast_node *passed_node);
t_ast_node	*parse_command(t_token **tokens);
t_ast_node	*init_node(t_token **tokens);
char		*expand(char *buff);
char		*get_envvar(char *pcdr);
char		*get_path(char *pcdr);
size_t		varsiz(const char *var);
size_t		pathsiz(const char *path);

//Helper Functions
void		lst_put(t_token *lst);
void		clean_shell(void);
void		put_err(char *msg);
void		print_ast(t_ast_node *node);
#endif