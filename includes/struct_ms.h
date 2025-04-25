/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:46:43 by souaret           #+#    #+#             */
/*   Updated: 2025/04/25 14:00:34 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MS_H
# define STRUCT_MS_H

/**************************************************************************
 * Global structure for minishell: 
 * 	cmd		: AST (abstract syntax tree) of the command line
 * 	envv	: environment variables
 * 	prompt	: prompt string
 * 	status	: status of the last command executed
 * 	sig		: signal handler
 * 	log_msg	: log message
 * 	paths	: paths available in current shell, PATH variable
 *
**************************************************************************/
typedef struct s_ms
{
	t_cmd	*cmd;
	t_exec	*exec;
	char	*prompt;
	int		status;
	int		sig;
	bool	log_msg;
	char	**paths;
	int		paths_len;
	char 	**args;
	char	**envv;
	int		envv_len;
}			t_ms;

t_ms	*ms_get(t_ms *ms);
void	ms_free(void);

#endif

