/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 23:07:32 by souaret           #+#    #+#             */
/*   Updated: 2025/01/19 01:57:56 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_UTILS_H
# define TOKENS_UTILS_H

// ERR_1 = "Error: token_get() failed"

/* --- error messages --- */
# define ERR_1 1 
# define ERR_1_MSG "Error: token_get() failed"

/* --- token types --- */
# define CMD_ECHO 1

/* --- token_utils.c --- */
t_token	*token_get(t_token *new_token);
t_token	*token_new(int type, char *str);
void	token_add(t_token **tokens, t_token *new);
void	tokens_free(void);

#endif