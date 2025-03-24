/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/24 12:21:06 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include <stddef.h>
# include "token.h"
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT_NAME "$minishell:"

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
	char	*var_shell[255];
	void	*cmd_table;
	char	*prompt;
}	t_minishell;

t_minishell	*getset_env(void *g);
t_token		*lexer(char *prompt);
int			parser(t_token *tokens);
void		open_prompt(void);
#endif