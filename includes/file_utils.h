/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:23:23 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 17:32:44 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
# define FILE_UTILS_H

void	ft_close_fd(int *fd);
void	ft_dup2(int *fd1, int fd2);
void	ft_pipe(int fd[2]);

#endif