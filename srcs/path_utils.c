/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:47:24 by souaret           #+#    #+#             */
/*   Updated: 2025/04/23 14:28:49 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************************
 * 
 * TODO: Faut-il garder les paths dans le cache,
 * 		ou les recalculer à chaque fois ?
 * 		car risque de travailler avec des variables obsoletes
 * 
************************************************************************/
char	**get_paths(void)
{
	t_exe	*exec;
	char	*path;

    exec = get_exec(NULL);
	do_check_error_exit((exec == NULL), ERR_EXEC_2);
	path = find_env(exec->envv, "PATH");
	do_check_error_exit((path == NULL), ERR_NO_PATH);
	if (exec->paths != NULL)
		free_str_vect(exec->paths);
	exec->paths = ft_split(path, ':');
	free_str(&path);
	do_check_error_exit(!exec->paths, ERR_MALLOC);
	return (exec->paths);
}