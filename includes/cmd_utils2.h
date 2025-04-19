/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:48:47 by souaret           #+#    #+#             */
/*   Updated: 2025/04/19 17:11:20 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_UTILS2_H
# define CMD_UTILS2_H

void	cmd_free_all(void);
int		ft_fork(t_cmd *cmd);
const	char	*cmd_print(int cmd_id);

#endif