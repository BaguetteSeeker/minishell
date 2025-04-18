/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:03:42 by souaret           #+#    #+#             */
/*   Updated: 2025/04/18 17:38:58 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/************************************************************************
 * 
 * Close file by it's File Descriptor (*fd or fd[])
 *   Skips if *fd is -1, 
 *   	or *fd is one of the system defaults:
 * 			STDIN_FILENO, or STDOUT_FILENO, or STDERR_FILENO
 * 
************************************************************************/
void	ft_close_fd(int *fd)
{
	if (*fd == -1 || *fd == STDIN_FILENO || *fd == STDERR_FILENO
		|| *fd == STDOUT_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		perror("close");
		free_and_exit(1);
	}
	*fd = -1;
}