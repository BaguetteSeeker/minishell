/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:57:34 by souaret           #+#    #+#             */
/*   Updated: 2025/04/23 14:50:20 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*************************************************************************
 * Getter for exec
*************************************************************************/
t_exec	*exec_get(t_exec *ex)
{
	static t_exec	*exec_var = NULL;

	if (exec_var != NULL && ex == NULL)
		return (exec_var);
	else if (exec_var == NULL && ex != NULL)
		exec_var = ex;
	return (exec_var);
}

/************************************************************************
 * Setter for exec
*************************************************************************/
static void	exec_set(t_exec *exec_var)
{
	exec_get(exec_var);
}

/************************************************************************
 * 
 * Initialization of exec structure
 * WARNING: this is the first function to call in the execution part.
 * 
*************************************************************************/
t_exec	*exec_init(char **envv)
{
	t_exec	*exec;

	exec = exec_get(NULL);
	if (exec == NULL)
		exec = (t_exec *)malloc(sizeof(t_exec));
	do_check_error_exit((exec == NULL), ERR_MALLOC);
	exec_set(exec);
	exec->paths = NULL;
	exec->paths_len = 0;
	exec->envv = envv;
	exec->envv_len = count_env(envv);
	return (exec);
}

/************************************************************************
 * Setter for exec
 * SIDI: 
 *		If exec is NULL, nothing to be done here !
 * TODO: voir si foncion libft qui nettoie un array de str [free_str_vect]
*************************************************************************/
void	exec_free(void)
{
	t_exec	*exec;
	int		i;

	exec = exec_get(NULL);
	if (exec == NULL)
		return ;
	if (exec->paths) 
	{
		free_str_vect(exec->paths);
		exec->paths = NULL;
	}
	exec->paths_len = 0;
	free(exec);
}

