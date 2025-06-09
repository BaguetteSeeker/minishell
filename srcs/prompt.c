/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:06:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 21:23:50 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_prompt(char *prompt, bool history)
{
	char	*input_line;

	input_line = readline(prompt);
	if (input_line == NULL)
	{
		if (g_getset(NULL)->state == MSH_PROMPTING_COMPLETION)
			return (NULL);
		else
			return (exit_shell(EXIT_MSG, 0), NULL);
	}
	else if (history == ADD_HISTORY && *input_line)
		add_history(input_line);
	return (input_line);
}

char	*wait_line(int fd, char *prompt)
{
	char	*line;

	line = NULL;
	while (1 && g_getset(NULL)->signal != SIGINT)
	{
		ft_putstr_fd(prompt, STDERR_FILENO);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strchr(line, '\n'))
		{
			ft_putendl_fd("", STDERR_FILENO);
			free(line);
			continue ;
		}
		if (ft_strchr(line, '\n'))
			line[ft_strlen(line) - 1] = '\0';
		break ;
	}
	return (line);
}

//Handles Minishell' routine
//!!! Expansion is called sequentially during execution
// one node at a time, on the content of the node to be executed
void	prompt_routine(t_minishell *msh_g)
{
	msh_g->mode = INTERACTIVE;
	while (1)
	{
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(
				get_var_value(VAR_SHELL, "PS1"), ADD_HISTORY);
		repl_once(msh_g);
	}
}
/* Tests ->
		msh_g->state = MSH_EXPANDING;
		msh_lstiter(msh_g->tokens, &expand_token);
		msh_lstiter(msh_g->tokens, &lst_put);

				expand_node(msh_g->cmd_table);
		if (msh_g->cmd_table->left)
			expand_node(msh_g->cmd_table->left);
		if (msh_g->cmd_table->right)
			expand_node(msh_g->cmd_table->right);
		print_ast(msh_g->cmd_table);
*/