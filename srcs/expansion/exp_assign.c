/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_rhs(char *entry, char *new_rhs)
{
	char	*eq = ft_strchr(entry, '=');

	if (!eq)
		return ;
	eq[1] = '\0';
	ft_strlcat(entry, new_rhs, ft_strlen(entry) + ft_strlen(new_rhs) + 1);
	free(new_rhs);
}

//expands RHS using segment expansion logic
static int	expand_rhs(char **vars)
{
	t_segment	**seg;
	char		*new;
	int			i;

	i = 0;
	while (vars[i])
	{
		seg = parse_segments(ft_strchr(vars[i], '=') + 1);
		if (!seg)
			return (1);
		expand_segments(seg);
		new = concat_segments(seg);
		if (!new)
			return (free_segments(seg), 1);
		replace_rhs(vars[i], new);
		free_segments(seg);
		i++;
	}
	return (0);
}

//returns 1 if LHS is expandable
static int	lhs_is_expandable(char *var)
{
	t_segment	**seg;
	int			is_expandable;
	char	 	*lhs;
	char	 	*eq;

	eq = ft_strchr(var, '=');
	if (!eq || eq == var)
		return (0);
	lhs = ft_substr(var, 0, eq - var);
	if (!lhs)
		return (0);
	seg = parse_segments(lhs);
	free(lhs);
	if (!seg)
		return (0);
	if (seg[0] && seg[0]->from_var)
		is_expandable = 1;
	free_segments(seg);
	return (is_expandable);
}

//puts formed "entry" into argv to be treated as a command
static int	handle_expandable_lhs(char **vars, t_ast_node *node)
{
	int		i;

	i = 0;
	while (vars[i])
	{
		if (lhs_is_expandable(vars[i]))
		{
			node->exp_args = malloc(sizeof(char *) * 2);
			if (!node->exp_args)
				return (1);
			node->exp_args[0] = ft_strdup(vars[i]);
			node->exp_args[1] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

//first expand every RHS that can be expanded
//if none of the LHS is expandable
// 	- return ;
//if at least one of the LHS is expandable : 
// 	- expand other side if expandable
// 	- build new_argv with said assignement
int	expand_vars(t_ast_node *node)
{
	if (!node->vars)
		return (0);
	if (expand_rhs(node->vars))
		return (1);
	if (handle_expandable_lhs(node->vars, node))
		return (1);
	return (0);
}
