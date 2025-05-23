/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gets cwd, move to target, update ENV accordingly
int	builtin_cd(t_ast_node *node)
{
	char	*target;
	char	cwd[1024];

	if (ft_ptrlen((const void **)node->args) != 1)
		return (ft_putendl_fd("cd: expected one argument", STDERR_FILENO), 1);
	target = node->args[0];
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd (before)");
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd: getcwd (before)");
		return (1);
	}
	update_add_env("OLDPWD", cwd);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd (after)");
		return (1);
	}	
	update_add_env("PWD", cwd);
	return (0);
}
