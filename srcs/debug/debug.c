/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:10:12 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/21 20:10:12 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	map_debug_flag(const char *name)
{
	if (ft_strcmp(name, "lexer") == 0)
		return DEBUG_LEXER_INPUT;
	if (ft_strcmp(name, "ast") == 0)
		return DEBUG_AST_ALL;
	if (ft_strcmp(name, "ast-content") == 0)
		return DEBUG_AST_CONTENT;
	if (ft_strcmp(name, "ast-draw") == 0)
		return DEBUG_AST_DRAW;
	if (ft_strcmp(name, "expansion") == 0)
		return DEBUG_EXP_ALL;
	if (ft_strcmp(name, "exp-segments") == 0)
		return DEBUG_EXP_SEGMENTS;
	if (ft_strcmp(name, "exp-splitting") == 0)
		return DEBUG_EXP_SPLITTING;
	if (ft_strcmp(name, "redir") == 0)
		return DEBUG_REDIR_LIST;
	if (ft_strcmp(name, "env") == 0)
		return DEBUG_ENV_EXTENDED;
	if (ft_strcmp(name, "all") == 0)
		return DEBUG_ALL;
	return DEBUG_NONE;
}

void	print_debug(t_minishell *msh, int applied)
{
	if (!applied)
		ft_dprintf(STDERR_FILENO, "msh: no debug flag provided after '--debug'\n");
	else
	{
		ft_dprintf(STDERR_FILENO, "msh: debugging enabled for: ");
		if (msh->debug_flags & DEBUG_LEXER_INPUT)
			ft_dprintf(STDERR_FILENO, "lexer ");
		if (msh->debug_flags & DEBUG_AST_CONTENT)
			ft_dprintf(STDERR_FILENO, "ast-content ");
		if (msh->debug_flags & DEBUG_AST_DRAW)
			ft_dprintf(STDERR_FILENO, "ast-draw ");
		if (msh->debug_flags & DEBUG_EXPANSION)
			ft_dprintf(STDERR_FILENO, "expansion ");
		if (msh->debug_flags & DEBUG_EXP_SEGMENTS)
			ft_dprintf(STDERR_FILENO, "exp-segments ");
		if (msh->debug_flags & DEBUG_EXP_SPLITTING)
			ft_dprintf(STDERR_FILENO, "exp-splitting ");
		if (msh->debug_flags & DEBUG_REDIR_LIST)
			ft_dprintf(STDERR_FILENO, "redir ");
		if (msh->debug_flags & DEBUG_ENV_EXTENDED)
			ft_dprintf(STDERR_FILENO, "env ");
		ft_dprintf(STDERR_FILENO, "\n");
	}
}
//set the bit(s) corresponding to this debug flag, preserving already-set bits
//using bitwise operator |= (inclusive OR)
static void	apply_debug_flags(char *flag_str, t_minishell *msh, int *applied)
{
	char	**flags;
	int		j;
	int		flag;

	flags = ft_split(flag_str, ',');
	if (!flags)
		return ;
	j = 0;
	while (flags[j])
	{
		flag = map_debug_flag(flags[j]);
		if (flag == DEBUG_NONE)
			ft_dprintf(STDERR_FILENO, "msh: unknown debug flag: %s\n", flags[j]);
		else
		{
			msh->debug_flags |= flag;
			*applied = 1;
		}
		free(flags[j]);
		j++;
	}
	free(flags);
}

//apply debug flags from a comma-separated list
void	parse_debug_flags(int *argc, char ***argv, t_minishell *msh)
{
	int		i;
	char	*arg;
	int		applied;
	int		found;

	i = 1;
	applied = 0;
	found = 0;
	while (i < *argc)
	{
		arg = (*argv)[i];
		if (ft_strncmp(arg, "--debug=", 8) == 0)
		{
			found = 1;
			apply_debug_flags(arg + 8, msh, &applied);
			while (i + 1 < *argc)
			{
				(*argv)[i] = (*argv)[i + 1];
				i++;
			}
			(*argv)[i] = NULL;
			(*argc)--;
			break;
		}
		i++;
	}
	if (found)
		print_debug(msh, applied);
}

int	is_debug_enabled(t_minishell *msh, t_debug_flags flag)
{
	int	is_debug;

	is_debug = msh->debug_flags & flag;
	return (is_debug);
}