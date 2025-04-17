/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:03:42 by souaret           #+#    #+#             */
/*   Updated: 2025/04/17 18:05:57 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell_so.h"

/************************************************************************
 * 
 * Close file by it's File Descriptor (fd[])
 *   Skips if fd is -1, or STDIN_FILENO, or STDOUT_FILENO, or STDERR_FILENO
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