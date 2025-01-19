/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:04:36 by souaret           #+#    #+#             */
/*   Updated: 2025/01/19 01:48:20 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_so.h"

/***************************************************************************
 * 
 *    Get the root pointer to [tokens]
 *      Provide [NULL] to get the pointer; this is the {getter}
 *      Provide a value to set the root pointer : this is he {setter}
 *
 *     // TODO: check if token is NULL ! (right before the return)
 *
 ***************************************************************************/
t_token	*token_get(t_token *new_token)
{
	static t_token	*token = NULL;

	//token = NULL;
	if (new_token != NULL)
	{
		token = new_token;
	}
	return (token);
}

/***************************************************************************
 * 
 *  Create and return a new node for a token 
 *      of type [type] 
 *      with the string [str]
 * 
***************************************************************************/
t_token	*token_new(int type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	ft_memset(new, 0, sizeof(t_token));
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}

/***************************************************************************
 * 
 *  Ajoute un token a la fin de la liste de tokens.
 * 
***************************************************************************/
void	token_add(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !new)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/***************************************************************************
 * 
 * Free all tokens
 *
***************************************************************************/
void	tokens_free(void)
{
	t_token	*tokens;
	t_token	*tmp;

	tokens = token_get(NULL);
	while (tokens)
	{
		tmp = (tokens)->next;
		free((tokens)->str);
		free(tokens);
		tokens = tmp;
	}
}
