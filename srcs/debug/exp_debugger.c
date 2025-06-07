/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_debugger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*quote_str(quote_t q)
{
	if (q == QUOTE_NONE)
		return ("NONE");
	if (q == QUOTE_SINGLE)
		return ("SINGLE");
	if (q == QUOTE_DOUBLE)
		return ("DOUBLE");
	return ("INVALID");
}

void	print_word_list(t_word *list)
{
	printf("\n === expansion debug ===\n");
	while (list)
	{
		printf("word : \t>%s< (ID %i)\n\tsplit: %i,\n\n\tfrom_var: %d\n",
			list->text,
			list->index,
			list->should_split,
			list->from_variable);
		list = list->next;
	}
}

void	print_segments(t_segment **seg)
{
	int	i;

	i = 0;
	printf("\n === === === seg debug ===\n");
	while (seg[i])
	{
		printf("\t|| segment %d:\t>%s<\n", i, seg[i]->text);
		printf("\t||\tquote: %s\n", quote_str(seg[i]->quote));
		printf("\t||\tfrom_var: %d\n", seg[i]->from_var);
		i++;
	}
}
