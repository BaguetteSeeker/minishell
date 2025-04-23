/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:15:39 by souaret           #+#    #+#             */
/*   Updated: 2025/04/23 14:35:07 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(int reason)
{
	//TODO: clean cmds
	// cmd_free_all()
	// TODO: clean files & fds
	// TODO: clean_signals
	exit(reason);
}

/********************************************************************
 * 
 *  Write a error message : [reason] 
 *		free what ever is needed to be freed
 *      and exit the program
 * 
*********************************************************************/
void	do_error_exit(int reason)
{
	ft_dprintf(STDERR_FILENO, "Error: %d\n", reason);
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
	perror("reason");
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

/********************************************************************
 * 
 * Free a mallocaed array of strings (char * or any kind of memory/pointer)
 *	 	that is null terminated
********************************************************************/
void	free_str_vect(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}