/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:37:25 by souaret           #+#    #+#             */
/*   Updated: 2025/01/27 19:39:46 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec();
char	*cmd_print(int cmd_id);

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

	cmd = NULL;
	cmd = cmd_create(CMD_ECHO, "Hello World!");
	do_check_error_exit((cmd == NULL), ERR_101);
	cmd_set(cmd);

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
	int		i;

	if (cmd != NULL)
	{
		printf("cmd type: %s, id = <%s>, param= <%s>, args = [", \
			(cmd->node_type == T_CMD ? "CMD" : "OPERATOR"), \
			cmd_print(cmd->cmd_id), cmd->cmd_str);
		if (cmd->cmd_args)
		{
			i = -1;
			while (cmd->cmd_args[++i])
				printf("<%s> ", cmd->cmd_args[i]);
		}
		printf(" ]\n");
		if (cmd->left)
		{
			printf("left: ");
			print_cmd_1_echo(cmd->left);
			printf("\n");
		}
		if (cmd->right)
		{
			printf("right: ");
			print_cmd_1_echo(cmd->right);
			printf("\n");
		}
		//printf("\n");
	}
}

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
