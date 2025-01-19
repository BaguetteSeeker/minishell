/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:16:22 by souaret           #+#    #+#             */
/*   Updated: 2025/01/19 01:55:53 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_UTILS_H
# define SYSTEM_UTILS_H

/* --- system_utils.c --- */
void	do_check_error_exit(bool error, int reason);
void	free_str(char *str);

#endif