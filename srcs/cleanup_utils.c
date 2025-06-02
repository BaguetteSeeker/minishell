/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:11:21 by epinaud           #+#    #+#             */
/*   Updated: 2025/05/13 20:21:39 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_value(t_token *token)
{
	static int	no_clean[] = {
		PIPE,
		AMPERSAND,
		OR_IF,
		AND_IF,
		LESS,
		GREAT,
		DLESS,
		DGREAT,
		OPAR,
		CPAR
	};

	if (!in_array(token->type, no_clean, sizeof(no_clean) / sizeof(int)))
	{
		free(token->value);
		token->value = NULL;
	}
}

//Recursively cleans the entire tree from bottom to top
//Double ptrs are freed right away,
//its subptrs pointing on already cleared token_lst
static void	clean_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		if (node->new_args)
			free_tab((void **)node->new_args);
		if (node->args)
			free(node->args);
		if (node->vars)
			free(node->vars);
		if (node->io_streams)
			msh_lstclear(&node->io_streams, NULL);
	}
	else if (node->type == NODE_OPERATOR || node->type == NODE_PIPE)
	{
		clean_ast(node->left);
		clean_ast(node->right);
	}
	else if (node->type == NODE_SUBSHELL)
		clean_ast(node->left);
	free(node);
}

void	clean_routine(void)
{
	t_minishell	*msh;

	msh = g_getset(NULL);
	if (msh->input)
		free(msh->input);
	if (msh->tokens)
		msh_lstclear(&msh->tokens, free_token_value);
	if (msh->cmd_table)
		clean_ast(msh->cmd_table);
	msh->input = NULL;
	msh->tokens = NULL;
	msh->cmd_table = NULL;
}

void	clean_shell(void)
{
	t_minishell	*msh;

	msh = g_getset(NULL);
	clean_routine();
	if (msh->var_env)
		ft_free_dynarr(msh->var_env);
	if (msh->var_shell)
		ft_free_dynarr(msh->var_shell);
	msh->var_env = NULL;
	msh->var_shell = NULL;
	rl_clear_history();
}

void	*chkalloc(char *val, char *msg)
{
	if (!val)
	{
		ft_putendl_fd(ERRMSG_MALLOC_FAIL, STDERR_FILENO);
		put_err(msg);
	}
	return (val);
}
