/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//joins every argument as a single line to simulate input
int script_args_routine(t_minishell *msh, int argc, char **argv)
{
	char	*input;
	t_token	*tokens_tmp;

	input = ft_strdup(argv[1]);
	for (int i = 2; i < argc; i++)
	{
		char *tmp = input;
		input = ft_strjoin(input, " ");
		free(tmp);
		tmp = input;
		input = ft_strjoin(input, argv[i]);
		free(tmp);
	}
	msh->input = input;
	msh->state = MSH_TOKENIZING;
	msh->tokens = tokenize(&msh->input, &msh->tokens);
	if (msh->state == MSH_FAILLURE)
		return (clean_routine(), 1);
	msh->state = MSH_EXPANDING;
	msh_lstiter(msh->tokens, &expand_token);
	msh->state = MSH_PARSING;
	tokens_tmp = msh->tokens;
	msh->cmd_table = parse_tokens(&tokens_tmp, NULL);
	draw_ast(msh->cmd_table, "", 1);
	msh->last_exitcode = execute_node(msh->cmd_table);
	if (msh->last_exitcode == 0)
		update_underscore(msh->cmd_table);
	clean_routine();
	return (msh->last_exitcode);
}

//extract lines from stdin line by line untile !line (EOF reached)
//for each line, execute as a regular prompt
int script_stdin_routine(t_minishell *msh)
{
	char	*line;
	size_t len = ft_strlen(msh->input);
	t_token	*tokens_tmp;

	line = get_next_line(0);
	while (line)
	{
		if (!line || *line == '\0')
		{
			free(line);
			continue;
		}
		msh->input = ft_strdup(line);
		if (len > 0 && msh->input[len - 1] == '\n')
			msh->input[len - 1] = '\0';
		printf("\n\t>%s<\n", msh->input);
		free(line);
		line = NULL;
		msh->state = MSH_TOKENIZING;
		msh->tokens = tokenize(&msh->input, &msh->tokens);
		if (msh->state == MSH_FAILLURE)
		{
			clean_routine();
			continue;
		}
		msh->state = MSH_EXPANDING;
		msh_lstiter(msh->tokens, &expand_token);
		msh->state = MSH_PARSING;
		tokens_tmp = msh->tokens;
		msh->cmd_table = parse_tokens(&tokens_tmp, NULL);
		draw_ast(msh->cmd_table, "", 1);
		msh->last_exitcode = execute_node(msh->cmd_table);
		if (msh->last_exitcode == 0)
			update_underscore(msh->cmd_table);
		clean_routine();
	line = get_next_line(0);
	}
	return (msh->last_exitcode);
}
