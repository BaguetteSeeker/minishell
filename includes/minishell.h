/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/29 22:16:04 by epinaud          ###   ########.fr       */
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
# include <sys/stat.h>

# define SHELL_NAME "msh"
# define PROMPT_NAME "\033[37;1m$minishell: \033[0m"
# define PS2 "> "
# define ERRMSG_SYNTAX ": syntax error near unexpected token `"
# define ERRMSG_MALLOC_FAIL "!!! MALLOC FAILLURE !!! :"
# define ERRMSG_MISSING_OPTOK "Uncatched Parsing Error : \
			Expecting Operator token but none was provided"
# define ERRMSG_EXPORT "msh: export: %s is not a valid identifier\n"
# define ERRMSG_NOCMD "msh: : command not found\n"
# define EXITC_NOCMD 127
# define EXITC_NOEXEC 126

# define COLOR_RED "\033[31;1m"
# define COLOR_TEAL "\033[0;36m"
# define COLOR_WHITE_BOLD "\033[37;1m"
# define COLOR_WHITE_BOLD_U "\033[1;4;37m"
# define COLOR_RESET "\033[0m"

typedef enum e_msh_state
{
	MSH_PROMPTING,
	MSH_PROMPTING_COMPLETION,
	MSH_TOKENIZING,
	MSH_EXPANDING,
	MSH_PARSING,
	MSH_EXECUTING,
	MSH_FAILLURE
}	t_msh_state;

typedef enum e_msh_mode
{
	INTERACTIVE,
	SCRIPT_ARGV,
	SCRIPT_STDIN
}	t_msh_mode;

//struct used to back stdin, stderr and stdout when redirecting in parent proc
typedef struct s_stdio {
	int stdin_fd;
	int stdout_fd;
	int stderr_fd;
}	t_stdio;

typedef struct s_minishell
{
	sig_atomic_t	state;
	t_msh_mode		mode;
	t_stdio			stdio;
	char			**var_env;
	char			**var_shell;
	char			*input;
	t_token			*tokens;
	t_ast_node		*cmd_table;
	int				last_exitcode;
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
# define LITTERAL_HEREDOC 0
# define EXPANDABLE_HEREDOC 127
# define ADD_HISTORY 1
# define NO_HISTORY 0
# define NO_EXIT_MSG 0
# define EXIT_MSG 1
# define VAR_ENV 0
# define VAR_SHELL 1

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
void		repl_once(t_minishell *msh_g);

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
void		exit_shell(bool exit_msg, int exit_code);

//Exec
int			execute_node(t_ast_node *node);
char		*get_cmdpath(char *cmd, char **envp);
char		**get_cmdargv(char *cmd, char **args);
int			redirections_handler(t_ast_node *node);
int			execute_pipe(t_ast_node *node);
int			execute_command(t_ast_node *node);
void		free_tab(void **tab);
char		**build_new_env(t_ast_node *node);
void		set_foreground_flag(t_ast_node *node);


//built-ins
t_bi_type	is_builtin(const char *cmd);
int			run_builtin(t_bi_type	builtin_type, t_ast_node *node);
int			builtin_pwd(void);
int			builtin_env(void);
int			builtin_exit(t_ast_node *node);
int			builtin_echo(t_ast_node *node);
int			builtin_cd(t_ast_node *node);
int			builtin_export(t_ast_node *node);
int			builtin_unset(t_ast_node *node);
void 		restore_stdio_builtin(void);
int 		redir_stdio_builtin(t_ast_node *node);


//env interface
char		**write_remmove_env(char **env, char *var_name);
char		**write_add_env(char **env, char *new_entry);
char		*get_new_entry(char *var_name, char *value);
char		**add_new_entry(char **env, char *new_entry);
char		**replace_new_entry(char **env, char *new_entry, int i);
char		*get_new_entry(char *var_name, char *value);
int			is_valid_export(char *name);

void		update_add_var(int mode, char *var_name, char *value);
void		update_remove_var(int mode, char *var_name);
char		*get_var_value(int mode, char *var_name);
char		*get_var_entry(int mode, char *var_name);
int			var_pos(char **var_tab, const char *var_name);


//shell, env and shell VAR
char		**init_shell_var(void);
char		**copy_env(char **env);
void		udapte_shell_var();
void		update_var_exitcode(void);
void		update_SHLVL(void);
void		update_underscore(t_ast_node *node);
void		script_args_routine(t_minishell *msh, int argc, char **argv);
void		script_stdin_routine(t_minishell *msh);
int			assign_shell_var(t_ast_node *node);
#endif