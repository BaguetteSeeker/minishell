/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:31:31 by epinaud           #+#    #+#             */
/*   Updated: 2025/04/22 15:18:42 by souaret          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "struct_cmds.h"
# include "builtin.h"
# include "cmd_exec.h"
# include "cmd_pipe.h"
# include "cmd_tree.h"
# include "cmd_utils.h"
# include "cmd_utils2.h"
# include "file_utils.h"
# include "system_utils.h"

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