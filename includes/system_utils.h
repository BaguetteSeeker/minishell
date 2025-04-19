/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:16:22 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 17:08:08 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_UTILS_H
# define SYSTEM_UTILS_H

typedef enum e_error
{
	ERR_0,
	ERR_NONE,
	ERR_MALLOC,
	ERR_CMD_NOT_FOUND,
	ERR_CMD_NOT_EXEC,
	ERR_FILE_NOT_FOUND,
	ERR_FILE_NOT_EXEC,
	ERR_FILE_NOT_DIR,
	ERR_FILE_NOT_PERM,
	ERR_FILE_NOT_PIPE,
	ERR_FILE_NOT_HEREDOC,
	ERR_FILE_NOT_INPUT,
	ERR_FILE_NOT_OUTPUT,
}	t_error;

/* --- system_utils.c --- */
void	free_and_exit(int status);
void	do_check_error_exit(bool error, int reason);
void	do_error_exit(int reason);
void	free_str(char **str);

#endif