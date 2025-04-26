/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:38 by souaret           #+#    #+#             */
/*   Updated: 2025/04/26 15:34:19 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * 
 * output Log Message: if flag is ON
 *		otherwise, remain silent [off]
 * 
*****************************************************************************/
/*************************************************************************
 * getter for minishell global var 
 * 		if param is NULL then it will set the global var
 * 		acting like a setter.
*************************************************************************/
t_ms	*ms_get(t_ms *ms)
{
	static t_ms	*ast_ms = NULL;

	if (ast_ms != NULL && ms == NULL)
		return (ast_ms);
	else if (ast_ms == NULL && ms != NULL)
		ast_ms = ms;
	// else
	// 	do_error_exit(ERR_EXEC_4);
	return (ast_ms);
}

/************************************************************************
 * Setter for ms
*************************************************************************/
static void	ms_set(t_ms *ms)
{
	ms_get(ms);
}

/************************************************************************
 * 
 * Initialization of global structure
 * WARNING: this is the first function to call in the execution part.
 * 
*************************************************************************/
t_ms	*ms_init(char **envv)
{
	t_ms	*ms;

	ms = ms_get(NULL);
	if (ms == NULL)
		ms = (t_ms *)malloc(sizeof(t_ms));
	do_check_error_exit((ms == NULL), ERR_MALLOC);
	ms_set(ms);
	ms->paths = NULL;
	ms->paths_len = 0;
	ms->envv = envv;
	ms->args = NULL;
	ms->cmd = NULL;
	ms->prompt = NULL;
	ms->status = 0;
	// ms->envv_len = count_env(envv);
	return (ms);
}

/************************************************************************
 * 
 * Free for global ms variables
 * 
*************************************************************************/
void	ms_free(void)
{
	t_ms	*ms;

	ms = ms_get(NULL);
	if (ms == NULL)
		return ;
	if (ms->paths) 
	{
		free_str_vect(ms->paths);
		ms->paths = NULL;
	}
	ms->paths_len = 0;
	// if (ms->envv) 
	// {
	// 	free_str_vect(ms->envv);
	// 	ms->envv = NULL;
	// }
	if (ms->cmd) 
	{
		cmd_delete_tree(ms->cmd);
		ms->cmd = NULL;
	}
	free_str((char **)&ms);
}

