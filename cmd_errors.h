/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:31 by souaret           #+#    #+#             */
/*   Updated: 2025/01/27 19:53:05 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ERRORS_H
# define CMD_ERRORS_H

# define ERR_1		1
# define ERR_MSG_1	"Error: memory allocation failed"
# define ERR_2		2
# define ERR_MSG_2	"Error: command tree is empty"

# define ERR_101		101
# define ERR_MSG_101	"Error: test_main_1"

# define ERR_CMD_0	0
# define MSG_CMD_0	"No nodes created"
# define ERR_CMD_1	1
# define MSG_CMD_1	"cmd_tree & cmd cannot be the identical"
# define ERR_CMD_2	2
# define MSG_CMD_2	"cannot create node string"
# define ERR_CMD_3	3 
# define MSG_CMD_3	"cannot add null child "
# define ERR_CMD_4	4 
# define MSG_CMD_4	"cannot add child (no left or right)"
# define ERR_CMD_5	5
# define MSG_CMD_5	"about to overright a child"
# define ERR_CMD_6	6
# define MSG_CMD_6	"cannot find root node (null)"

#endif
