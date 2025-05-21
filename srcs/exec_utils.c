/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anle-pag <anle-pag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:20:00 by anle-pag          #+#    #+#             */
/*   Updated: 2025/05/18 18:20:00 by anle-pag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}

char	**get_envpaths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split((envp[i] + 5), ':'));
		i++;
	}
	return (NULL);
}

char	*get_newpath(char *path, char *cmd, int i)
{
	int		lenpath;
	int		lencmd;
	char	*newpath;

	if (!path || !cmd)
		return (NULL);
	lenpath = ft_strlen(path);
	lencmd = ft_strlen(cmd);
	newpath = malloc(sizeof(char) * lenpath + lencmd + 2);
	if (!newpath)
		return (free(newpath), NULL);
	i = 0;
	while (i < lenpath)
	{
		newpath[i] = path[i];
		i++;
	}
	newpath[i++] = '/';
	while (i < (lenpath + lencmd + 1))
	{
		newpath[i] = cmd[i - lenpath - 1];
		i++;
	}
	newpath[lenpath + lencmd + 1] = '\0';
	return (newpath);
}

//trop long
char	**get_cmdargv(char *cmd, char **args)
{
	char	**argv;
	size_t	argc;
	size_t	i;

	argc = 0;
	i = 0;
	while (args && args[argc])
		argc++;
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd);
	if (!argv[0])
		return (free(argv), NULL);
	while (i < argc)
	{
		argv[i + 1] = strdup(args[i]);
		if (!argv[i + 1])
		{
			while (i >= 0)
				free(argv[i--]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[argc + 1] = NULL;
	return (argv);
}

//eventually should handle persmission error
//error_exit("permission denied: ", arg, EXIT_NOEXEC, NULL);
char	*get_cmdpath(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**envpaths;

	i = -1;
	path = NULL;
	if ((*cmd == '/' || *cmd == '.') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if ((*cmd == '/' || *cmd == '.') && access(cmd, F_OK | X_OK) != 0)
		return (printf("permission denied: %s", cmd), NULL); //here
	if (!envp || *envp == NULL || *cmd == '\0')
		return (NULL);
	envpaths = get_envpaths(envp);
	while (envpaths[++i])
	{
		path = get_newpath(envpaths[i], cmd, i);
		if (access(path, F_OK | X_OK) == 0)
			return (free_tab((void **)envpaths), path);
		free(path);
	}
	free_tab((void **)envpaths);
	return (NULL);
}
