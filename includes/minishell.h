/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/20 12:57:21 by epinaud          ###   ########.fr       */
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
# include <sys/wait.h>

# define PROMPT_NAME "$minishell: "
# define PS2 "> "
# define ERRMSG_SYNTAX "msh: syntax error near unexpected token `"
# define ERRMSG_MALLOC_FAIL "!!! MALLOC FAILLURE !!! :"
# define ERRMSG_MISSING_OPTOK "Uncatched Parsing Error : \
			Expecting Operator token but none was provided"
# define EXITC_NOCMD 127
# define EXITC_NOEXEC 126

# define COLOR_RED "\033[31;1m"
# define COLOR_TEAL "\033[0;36m"
# define COLOR_WHITE_BOLD "\033[37;1m"
# define COLOR_WHITE_BOLD_U "\033[1;4;37m"
# define COLOR_RESET "\033[0m"

typedef enum s_msh_state
{
	MSH_PROMPTING,
	MSH_TOKENIZING,
	MSH_HRDC_PROMPTING,
	MSH_EXPANDING,
	MSH_PARSING,
	MSH_EXECUTING,
	MSH_FAILLURE
}	t_msh_state;

//should add a 
//char *last_arg;
//for $?
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
# define CHR_SQUOTE '\''
# define CHR_DQUOTE '\"'
# define XPD_ALL 0
# define XPD_HDOC_VARS 1
# define XPD_HDOC 2
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
void		draw_ast(t_ast_node *node, const char *prefix, int is_left);
void		*chkalloc(char *val, char *msg);
void		set_sigaction(void (sighandle)(int, siginfo_t *, void *));
void		signals_handler(int sig, siginfo_t *siginfo, void *context);
void		exit_shell(bool exit_msg);
char		**copy_env(char **env);

//Exec
int			execute_node(t_ast_node *node);
char		*get_cmdpath(char *cmd, char **envp);
char		**get_cmdargv(char *cmd, char **args);
int			redirections_handler(t_ast_node *node);
int			execute_pipe(t_ast_node *node);
void		free_tab(void **tab);

//built-ins
t_builtin_type	is_builtin(const char *cmd);
int		run_builtin(t_builtin_type	builtin_type, t_ast_node *node);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_exit(void);
int		builtin_echo(t_ast_node *node);
int		builtin_cd(t_ast_node *node);
int		builtin_export(t_ast_node *node);
int		builtin_unset(t_ast_node *node);
char	**write_new_env(char **env, char *new_entry);
void	update_add_env(char *var_name, char *value);
void	update_remove_env(char *var_name);
char	**write_remmove_env(char **env, char *var_name);
char	**write_add_env(char **env, char *new_entry);
char	*get_new_entry(char *var_name, char *value);
int		var_pos(char **env, const char *var_name);

#endif