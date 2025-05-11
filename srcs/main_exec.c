/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidi <sidi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:11:46 by souaret           #+#    #+#             */
/*   Updated: 2025/05/09 17:34:03 by sidi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************************
 *
 * 
*************************************************************************/
int	main1(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	t_cmd	*root;
	t_ms	*ms;

	if (argc > 1)
	{
		(void) env;
		ms = ms_init(env);
		do_check_error_exit((ms == NULL), ERR_EXEC_5);
		builtin_init();
		cmd = node_new(argv[1]);
		cmd->cmd_args = argv + 1; // "/bin/ls -l"
		root = node_add_top(NULL, cmd);
		cmd_set(root);
		cmd_exec();
	}
	else
		ft_printf("\n --- Usage: %s <cmd param1 param2...\n\n", argv[0]);
	return (0);
}

/************************************************************************
 *
 * 
*************************************************************************/
int	main2(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd, *cmd_ls, *cmd_wc;
	t_cmd	*root;
	t_ms	*ms;

	if (argc > 1)
	{
		(void)env;
		ms = ms_init(env);
		do_check_error_exit((ms == NULL), ERR_EXEC_5);
		builtin_init();
		// create AST for "ls | wc"
		cmd_ls = node_new("/bin/ls");
		cmd_ls->cmd_args = (char *[]){"/bin/ls", "-l",  NULL};

		cmd_wc = node_new("/bin/wc");
		cmd_wc->cmd_args = (char *[]){"/bin/wc", "-lw",  NULL};

		cmd = node_new("|");
		cmd->node_type = N_OPE_PIPE;
		cmd->left = cmd_ls;
		cmd->right = cmd_wc;
		//cmd->cmd_str = ft_strdup("|");
		//cmd->cmd_id = CMD_PIPE;
		cmd->is_child = false;
		cmd->is_builtin = false;
		root = cmd; 	//node_add_top(NULL, cmd_ls);

		// cmd = node_new(argv[1]);
		// cmd->cmd_args = argv + 1; // "/bin/ls -l"
		//root = node_add_top(NULL, cmd);
		cmd_set(root);
		cmd_exec();
	}
	else
		ft_printf("\n --- Usage: %s <cmd param1 param2...\n\n", argv[0]);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	//main1(argc, argv, env);	// /bin/ls -l
	main2(argc, argv, env);	// ls | wc
	return (0);
}
