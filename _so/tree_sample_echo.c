/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sample_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:34:51 by souaret           #+#    #+#             */
/*   Updated: 2025/01/19 01:41:51 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_so.h"

/***************************************************************************
 * 
 * Create list for: 
 *      echo Hello World!"
 * 
***************************************************************************/
t_token	*create_list_1_echo(void)
{
	t_token	*tokens;
	t_token	*t;

	tokens = token_get(NULL);
	do_check_error_exit((tokens == NULL), ERR_1);
	t = token_new(CMD_ECHO, "Hello World!");
	token_add(&tokens, t);
	t = token_new(CMD_ECHO, "Hello 2nd");
	token_add(&tokens, t);
	// another way to do it :
	// add_token(tokens, new_token(CMD_ECHO, "Hello World!", );
	return (tokens);
}

/***************************************************************************
 * 
 * 
 * 
***************************************************************************/
void	print_list_1_echo(t_token *tokens)
{
	t_token	*t;
	int		i;
	char	**s;

	t = tokens;
	i = 0;
	while (t != NULL)
	{
		printf("%d: Token type: %d, Token value: <%s> args = ", \
		i++, t->type, t->str);
		s = t->args;
		if (!s)
			printf("<no args>");
		while (s && *s)
		{
			printf("[%s] ", *s);
			s++;
		}
		printf("\n");
		t = t->next;
	}
}

/***************************************************************************
 * 
 * 
 * 
***************************************************************************/
void	free_list_1_echo(t_token *tokens)
{
	t_token	*t;
	t_token	*tmp;

	t = tokens;
	while (t != NULL)
	{
		tmp = t;
		t = t->next;
		free_str(tmp->str);
		free_str((char *)tmp->args);
		free(tmp);
	}
}

/***************************************************************************
 * 
 * 
 * 
***************************************************************************/
int	main_1(void)
{
	t_token	*tokens;

	tokens = create_list_1_echo();
	if (!tokens)
		exit(-1);
	print_list_1_echo(tokens);
	free_list_1_echo(tokens);
	return (0);
}
