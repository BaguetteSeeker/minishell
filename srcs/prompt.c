/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:06:38 by epinaud           #+#    #+#             */
/*   Updated: 2025/06/09 12:21:56 by epinaud          ###   ########.fr       */
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
			return (exit_shell(EXIT_MSG), NULL);
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
		ft_putendl_fd(prompt, STDERR_FILENO);
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
	t_token		*tokens_tmp;

	while (1)
	{
		msh_g->state = MSH_PROMPTING;
		msh_g->input = open_prompt(PROMPT_NAME, ADD_HISTORY);
		if (ft_strncmp(msh_g->input, "exit", 4) == 0)
			exit_shell(EXIT_MSG);
		msh_g->state = MSH_TOKENIZING;
		msh_g->tokens = tokenize(&msh_g->input, &msh_g->tokens);
		if (msh_g->state == MSH_FAILLURE)
		{
			clean_routine();
			continue ;
		}
		msh_g->state = MSH_PARSING;
		tokens_tmp = msh_g->tokens;
		msh_g->cmd_table = parse_tokens(&tokens_tmp, NULL);
		msh_g->state = MSH_EXECUTING;
		clean_routine();
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