/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_exec.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:49:23 by souaret           #+#    #+#             */
/*   Updated: 2025/04/23 14:24:17 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_EXEC_H
# define STRUCT_EXEC_H

# define ERR_EXEC_0	0
# define ERR_EXEC_MSG_0	"Error: Exec 0"
# define ERR_EXEC_1	1
# define ERR_EXEC_MSG_1 "Error: Cannot initialize exec variables"
# define ERR_EXEC_2	2
# define ERR_EXEC_MSG_2	"Error: Exec variable is NULL"
# define ERR_EXEC_3	3
# define ERR_EXEC_MSG_3	"Error: Exec 3"

/**************************************************************************
 * 
 * Executions variables: 
 *		paths	    : paths available in current shell, PATH variablee
 *		paths_len   : number of paths : TODO: do we need this ?
 * 
**************************************************************************/
typedef struct s_exec
{
	char	**paths;
	int		paths_len;
	char	**envv;
	int		envv_len;
	int		status;
}			t_exec;

#endif