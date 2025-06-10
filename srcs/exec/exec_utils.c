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

//searches for executable in $PATH
static char	**get_path_array(char **envp)
{
	char	**envpaths;
	char	*path_value;

	envpaths = get_envpaths(envp);
	if (envpaths)
		return (envpaths);
	path_value = get_var_value(VAR_SHELL, "PATH");
	if (path_value)
		return (ft_split(path_value, ':'));
	return (ft_split(".", ':'));
}

static char	*search_path_dirs(char *cmd, char **envp)
{
	char		**envpaths;
	char		*path;
	struct stat	st;
	int			i;

	envpaths = get_path_array(envp);
	if (!envpaths)
		return (NULL);
	i = 0;
	while (envpaths[i])
	{
		path = get_newpath(envpaths[i], cmd, i);
		if (access(path, F_OK) == 0 && stat(path, &st) == 0
			&& !S_ISDIR(st.st_mode))
			return (free_tab((void **)envpaths), path);
		free(path);
		i++;
	}
	free_tab((void **)envpaths);
	return (NULL);
}

//returns path to command
//	-if command not found : return NULL
//	-if file found but not accessible
char	*get_cmdpath(char *cmd, char **envp)
{
	struct stat	st;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_dprintf(STDERR_FILENO, "msh: %s: is a directory\n", cmd);
			clean_shell();
			exit(EXITC_NOEXEC);
		}
		return (cmd);
	}
	return (search_path_dirs(cmd, envp));
}
