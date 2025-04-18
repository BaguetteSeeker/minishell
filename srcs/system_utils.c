/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:15:39 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:41:50 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/********************************************************************
 * 
 *  Write a error message : [reason] 
 *		free what ever is needed to be freed
 *      and exit the program
 * 
*********************************************************************/
void	do_error_exit(int reason)
{
	ft_printf_fd("Error: %d\n", reason, STDERR_FILENO);
	//TODO: free tokens
	//tokens_free();
	//TODO: clean cmds
	// cmd_free_all()
	// TODO:
	// free all the memory variables [...]
	exit(reason);
}

/********************************************************************
 * 
 *  Check if a condition [error] 
 *		if false then all is ok
 *		if true then :  display [reason] 
 *                      free what ever is needed to be freed
 *                      and exit the program
 * 
*********************************************************************/
void	do_check_error_exit(bool error, int reason)
{
	if (error == false)
		return ;
	if (reason != 0)
	do_error_exit(reason);
}

/********************************************************************
 * 
 * Free a mallocaed memory (char * or any kind of memory/pointer)
 * 
********************************************************************/
void	free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}
