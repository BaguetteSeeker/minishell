/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//REPL stands for Read-Evaluation-Print Loop
//this function describes one iteration of the REPL
// !!! input must be set in respective mode loops !!!
void repl_once(t_minishell *msh_g)
{
	t_token *tmp;

	if (!msh_g->input)
		return ;
	msh_g->state = MSH_TOKENIZING;
	msh_g->tokens = tokenize(&msh_g->input, &msh_g->tokens);
	if (msh_g->state == MSH_FAILLURE)
	{
		clean_routine();
		return;
	}
	msh_g->state = MSH_EXPANDING;
	msh_lstiter(msh_g->tokens, &expand_token);
	msh_g->state = MSH_PARSING;
	tmp = msh_g->tokens;
	msh_g->cmd_table = parse_tokens(&tmp, NULL);
	draw_ast(msh_g->cmd_table, "", 1);
	msh_g->state = MSH_EXECUTING;
	msh_g->last_exitcode = execute_node(msh_g->cmd_table);
	if (msh_g->last_exitcode == 0)
		update_underscore(msh_g->cmd_table);
	udapte_var_shell();
	clean_routine();
}
