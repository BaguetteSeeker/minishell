/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 12:54:58 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//helper for expand_rhs
//replace in place since no word splitting in assignement
void	replace_rhs(char *entry, char *new_rhs)
{
	char	*eq;

	eq = ft_strchr(entry, '=');
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

//first expand every RHS that can be expanded
int	expand_vars(t_ast_node *node)
{
	if (!node->vars)
		return (0);
	if (expand_rhs(node->vars))
		return (1);
	return (0);
}
