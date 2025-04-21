/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:11:46 by souaret           #+#    #+#             */
/*   Updated: 2025/04/21 18:42:52 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	t_cmd	*root;

	if (argc > 1)
	{
		(void)env;
		builtin_init();
		cmd = node_new(argv[1]);
		cmd->cmd_args = argv + 1; //ft_split("pwd Hello World", ' ');
		root = node_add_top(NULL, cmd);
		cmd_set(root);
		cmd_exec();
	}
	else
		ft_printf("\n --- Usage: %s <cmd param1 param2...\n\n", argv[0]);
	return (0);
}
