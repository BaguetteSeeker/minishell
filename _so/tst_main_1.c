/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:37:25 by souaret           #+#    #+#             */
/*   Updated: 2025/01/25 17:34:48 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>

/***************************************************************************
 * 
 * Create tree for: echo Hello World!"
 * 
***************************************************************************/
t_cmd	*create_cmd_1_echo(void)
{
	t_cmd	*cmd;

	cmd = cmd_create(CMD_ECHO, "Hello World!");
	// t_token	*tokens;
	// t_token	*t;

	// cmd = NULL;
    // cmd_set(NULL);
    // cmd_
	// do_check_error_exit((tokens == NULL), ERR_1);
	// t = token_new(CMD_ECHO, "Hello World!");
	// token_add(&tokens, t);
	// t = token_new(CMD_ECHO, "Hello 2nd");
	// token_add(&tokens, t);
	// // another way to do it :
	// // add_token(tokens, new_token(CMD_ECHO, "Hello World!", );
	return (cmd);

}

/***************************************************************************
 * 
 * 
 * 
***************************************************************************/
void	print_cmd_1_echo(t_cmd	*cmd)
{
	if (cmd != NULL)
	{
		printf("cmd type: %d, value: <%s> args = ", \
		 	cmd->node_type, cmd->cmd_str);
		if (cmd->left)
		{
			printf("left: ");
			print_cmd_1_echo(cmd->left);
			printf("\n");
		}
		if (cmd->right )
		{
			printf("right: ");
			print_cmd_1_echo(cmd->right);
			printf("\n");
		}
		printf("\n");
	}
}

void cmd_exec(void);

/************************************************************************
 * 
 * TODO: WIP    -  Work in progress
*************************************************************************/
void	main_1(void)
{
	t_cmd	*cmd;

	cmd = create_cmd_1_echo();
	if (!cmd)
		exit(-1);
	print_cmd_1_echo(cmd);
	cmd_exec();
}

/************************************************************************
 * 
 * 
 * 
*************************************************************************/
int	main(void)
{
	main_1();
	return (0);
}
