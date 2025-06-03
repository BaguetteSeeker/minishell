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

//checks if any LHS in var=val assignments contains a variable reference
//returns 1 if at least one is expandable (e.g. "VAR1=2 $VAR2=oui"), 0 otherwise
static int	has_expandable_lhs(char **vars)
{
	int		i;
	char	*eq;

	i = 0;
	while (vars[i])
	{
		eq = ft_strchr(vars[i], '=');
		if (!eq)
			return (0);
		*eq = '\0';
		if (ft_strchr(vars[i], '$'))
		{
			*eq = '=';
			return (1);
		}
		*eq = '=';
		i++;
	}
	return (0);
}

//expands the RHS of an assignment using segment parsing and concatenation
//returns the expanded string, or NULL on error or empty variable
static char	*expand_side(char *rhs)
{
	t_segment	**seg;
	char		*result;

	seg = parse_segments(rhs);
	if (!seg)
		return (NULL);
	expand_segments(seg);
	result = concat_segments(seg);
	if (!result)
		result = ft_strdup("");
	free_segments(seg);
	return (result);
}

//expands all RHS values in a var=val list and rebuilds each assignment
//returns a new array of assignments or NULL on allocation failure
static char	**expand_assignments(char **vars)
{
	char	**new;
	char	*eq;
	char	*rhs;
	char	*lhs;
	int		i;

	new = malloc(sizeof(char *) * (ft_ptrlen((const void **)vars) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (vars[++i])
	{
		eq = ft_strchr(vars[i], '=');
		if (!eq)
			return (free_tab((void **)new), NULL);
		*eq = '\0';
		rhs = expand_side(eq + 1);
		lhs = ft_substr(vars[i], 0, eq - vars[i]);
		new[i] = ft_strjoin2(lhs, "=", rhs);
		*eq = '=';
		if (!new[i])
			return (free_tab((void **)new), NULL);
	}
	new[i] = NULL;
	return (new);
}

// === cursed segfaulter do not call ===
//
//if none of the LHS is expandable
// 	- expand every RHS that can be expanded
// 	- return ;
//if at least one of the LHS is expandable : 
// 	- expand too
// 	- expand other side if expandable
// 	- finally build new_argv with said assignement
int	expand_vars(t_ast_node *node)
{
	char	**expanded;

	if (!node || !node->vars || !node->vars[0])
		return (0);
	expanded = expand_assignments(node->vars);
	if (!expanded)
		return (1);
	if (!has_expandable_lhs(node->vars))
	{
		node->exp_vars = expanded;
		return (0);
	}
	node->exp_args = expanded;
	return (1);
}
