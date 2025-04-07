/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/07 23:55:43 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include "token.h"
# include "cmd_table.h"
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT_NAME "$minishell:"
# define PS2 "> "
# define ERR_MSG_SYNTAX "syntax error near unexpected token `"
# define QUOTES_SET "\"\'" 

/*********************************************
 *
 key   : The name of the environment variable (e.g., "PATH")
 value : The value of the environment variable (e.g., "/usr/bin")
 next  : Pointer to the next environment variable
 *
*********************************************/
// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

typedef struct s_minishell
{
	t_token	*tok_lst;
	char 	**var_env;
	char	**var_shell;
	void	*cmd_table;
	char	*prompt;
}	t_minishell;

t_minishell	*getset_env(void *g);
t_token		*tokenize(char *prompt, t_token *token_head);
int			parser(t_token *tokens);
char		*open_prompt(char *prompt);
void		handle_heredocs(t_token *token);
char		*new_heredoc(char *delimiter, bool apd_newline);
void		lst_put(t_token *lst);
void		put_err(char *msg);
void		free_token_value(t_token *token);
#endif