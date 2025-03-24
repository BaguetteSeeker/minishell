/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:12:51 by epinaud           #+#    #+#             */
/*   Updated: 2025/03/24 11:08:00 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_parenthesis(char *str, size_t side)
// {
// 	return (str);
// }

int	parser(t_token *tokens)
{
	while (tokens)
	{
		//if logic
			//Allocate logic node
			//
		//Allocate cmd_node
		//Add cmd_name
		//Add cmd_args
		tokens = tokens->next;
	}
	return (0);
}
