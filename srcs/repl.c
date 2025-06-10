/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/06/10 16:38:35 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//REPL stands for Read-Evaluation-Print Loop
//this function describes one iteration of the REPL
//!!! input must be set in respective mode loops !!!
//debug functions :
//	-MSH_LSTITER(msh_g->tokens, &expand_token);
//	-print_ast(msh_g->cmd_table);
//	-draw_ast(msh_g->cmd_table, "", 1);
void	repl_once(t_minishell *msh_g)
{
	t_token	*tokens_tmp;

	if ((!msh_g->input || *msh_g->input == '\0'))
		return (clean_routine());
	msh_g->state = MSH_TOKENIZING;
	msh_g->tokens = tokenize(&msh_g->input, &msh_g->tokens);
	if (msh_g->state == MSH_FAILLURE)
	{
		msh_g->last_exitcode = 2;
		set_exitcode(2);
		clean_routine();
		return ;
	}
	msh_g->state = MSH_PARSING;
	tokens_tmp = msh_g->tokens;
	msh_g->cmd_table = parse_tokens(&tokens_tmp, NULL);
	msh_g->state = MSH_EXECUTING;
	msh_g->last_exitcode = execute_node(msh_g->cmd_table);
	clean_routine();
}
