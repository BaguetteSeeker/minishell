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

//move the current working directory
int	builtin_cd(t_ast_node *node)
{
	char	*target;
	char	cwd[1024];

	if (!node->exp_args[1] || !*node->exp_args[1])
		return (ft_putendl_fd("cd: expected an argument", STDERR_FILENO), 1);
	if (ft_ptrlen((const void **)node->exp_args) > 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	target = node->exp_args[1];
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("cd: "), 1);
	if (chdir(target) != 0)
		return (ft_dprintf(STDERR_FILENO, ERRMSG_CD, target), 1);
	update_add_var(VAR_ENV, "OLDPWD", cwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("cd: "), 1);
	update_add_var(VAR_ENV, "PWD", cwd);
	return (0);
}
