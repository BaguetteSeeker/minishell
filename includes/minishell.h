/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/27 14:19:34 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include <stddef.h>
# include <libft.h>
# include "token.h"
# include "cmd_table.h"
# include "lltype_converts.h"
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_NAME "msh"
# define PROMPT_NAME "$minishell: "
# define PS2 "> "
# define ERRMSG_SYNTAX ": syntax error near unexpected token `"
# define ERRMSG_MALLOC_FAIL "!!! MALLOC FAILLURE !!! :"
# define ERRMSG_MISSING_OPTOK "Uncatched Parsing Error : \
			Expecting Operator token but none was provided"

typedef enum s_msh_state
{
	MSH_PROMPTING,
	MSH_TOKENIZING,
	MSH_BLOCKING_PROMPT,
	MSH_EXPANDING,
	MSH_PARSING,
	MSH_EXECUTING,
	MSH_FAILLURE
}	t_msh_state;

typedef struct s_minishell
{
	t_msh_state	state;
	char		**var_env;
	char		**var_shell;
	char		*input;
	t_token		*tokens;
	t_ast_node	*cmd_table;
	int			last_exitcode;
}	t_minishell;

//Functions' Flags
# define GET 0
# define QUOTES_SET "\"\'"
# define PARSE_SUBSQ_WORDS 1
# define PARSE_SUBSQ_VARS 2
# define TYPE_DLRS 1
# define TYPE_WCRD 2
# define TYPE_CODE 3
# define CHR_SQTE '\''
# define CHR_DQTE '\"'
# define XPD_ALL 0
# define XPD_HDOC 1
# define XPD_REDIR 2
# define EXPANDABLE_HEREDOC 127
# define LITTERAL_HEREDOC 0
# define ADD_HISTORY 1
# define NO_HISTORY 0
# define NO_EXIT_MSG 0
# define EXIT_MSG 1

//Core Prototypes
t_minishell	*g_getset(void *g);
void		prompt_routine(t_minishell *msh_g);
char		*open_prompt(char *prompt, bool history);
t_token		*tokenize(char **inpt_ptr, t_token **token_head);
void		handle_heredoc(t_token *token);
t_ast_node	*parse_tokens(t_token **tokens, t_ast_node *passed_node);
t_ast_node	*parse_command(t_token **tokens);
t_ast_node	*init_node(t_token **tokens);
bool		check_varname(char *str);
char		*expand(char *buff, size_t flag);
void		expand_token(t_token *tokens);
void		expand_node(t_ast_node *node);
char		*get_envvar(char *pcdr);
char		*get_path(char *pcdr);
size_t		varsiz(const char *var);
size_t		pathsiz(const char *path);

//Helper Functions
void		lst_put(t_token *lst);
void		clean_shell(void);
void		clean_routine(void);
void		free_token_value(t_token *token);
void		put_err(char *msg);
void		print_ast(t_ast_node *node);
void		*chkalloc(char *val, char *msg);
void		set_sigaction(void (sighandle)(int, siginfo_t *, void *));
void		signals_handler(int sig, siginfo_t *siginfo, void *context);
void		exit_shell(bool exit_msg);
#endif