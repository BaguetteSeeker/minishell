/******************************************
 * env_utils.h
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************
 *
 * Dynamic array to store environment variables
 *
****************************************************/
/*****************************************************************************
 * 
 * Output Log Message: if flag is ON
 * 		otherwise, remain silent [off]
 * 
*****************************************************************************/
void	putlog_fd(char *log_message)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	if (!minishell)
		show_error_exit(ERR_7);
	if (minishell->log_msg)
		ft_putendl_fd(log_message, STDERR);
}

/****************************************************
* Count the number of environment variables in envp
****************************************************/
int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

/****************************************************
 * Initialize the environment variables from envp
****************************************************/
void	init_env(char **envp)
{
	char	**envv;
	int count;

	count = count_env(envp);
	envv = (char **)malloc((count + 1) * sizeof(char *));
	if (!envv)
		minishell_exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		envv[i] = ft_strdup(envp[i]);
		if (!envv[i])
			minishell_exit(EXIT_FAILURE);
		i++;
	}
	envv[count] = NULL;
	putlog_fd("Environment variables initialized with %d variables.\n", count);
}

/****************************************************
 * Add or update an environment variable
	length =  [key=value\0] --> + 2
****************************************************/
void	add_env(char **envv, const char *key, const char *value)
{
	int		key_len;
	char	*new_var;
	char	**new_envv;
	int		count;
	int		i;

	key_len = ft_strlen(key);
	new_var = (char *)malloc(key_len + ft_strlen(value) + 2);
	if (!new_var)
		minishell_exit(EXIT_FAILURE);
	putlog_fd("new var: %s=%s", key, value);
	// ---- Check if the key already exists
	i = 0;
	while (envv[i])
	{
		if (ft_strncmp(envv[i], key, key_len) == 0 && envv[i][key_len] == '=')
		{
			free(envv[i]);
			envv[i] = new_var;
			putlog_fd("Environment variable '%s' updated.\n", key);
			return ;
		}
		i++;
	}
	// Add a new environment variable
	count = count_env(envv);
	new_envv = (char **)realloc(envv, (count + 2) * sizeof(char *));
	if (!new_envv) 
	{
		free(new_var);
		minishell_exit(EXIT_FAILURE);
	}
	envv = new_envv;
	envv[count] = new_var;
	envv[++count] = NULL;
	putlog_fd("Environment variable '%s' added.\n", key);
}

/****************************************************
 * Find an environment variable by key
****************************************************/
char	*find_env(char **envv, const char *key)
{
	int key_len;
	int	count;
	int	i;

	key_len = ft_strlen(key);
	count = count_env(envv);
	i = 0;
	while (envv[i])
	{
		if (ft_strncmp(envv[i], key, key_len) == 0 && envv[i][key_len] == '=')
		{
			putlog_fd("Environment variable '%s' found: %s\n", key, \
				envv[i] + key_len + 1);
			return envv[i] + key_len + 1;
		}
		i++;
	}
	putlog_fd("Environment variable '%s' not found.\n", key);
	return NULL;
}

/****************************************************
 * Delete an environment variable
****************************************************/
void	delete_env(char **envv, const char *key)
{
	int	key_len;
	int	i;

	key_len = ft_strlen(key);
	i = 0;
	while (envv[i])
	{
		if (ft_strncmp(envv[i], key, key_len) == 0 && envv[i][key_len] == '=')
		{
			free(envv[i]);
			// Shift remaining variables
			while (envv[i + 1])
			{
				envv[i] = envv[i + 1];
				i++;
			}
			envv[i--] = NULL;
			putlog_fd("Environment variable '%s' deleted.\n", key);
			return ;
		}
		i++;
	}
	putlog_fd("Environment variable '%s' not found.\n", key);
}

/****************************************************
 * Free all environment variables
****************************************************/
void	free_env(char **envv)
{
	int	i;

	i = 0; 
	while (envv[i])
	{
		free(envv[i]);
		i++;
	}
	free(envv);
	envv = NULL;
	putlog_fd("All environment variables freed.\n");
}

/****************************************************
 * Print all environment variables (for debugging)
****************************************************/
void	print_env(char **envv)
{
	int	i;

	putlog_fd("Environment variables:\n");
	i = 0;
	while (envv[i] 
	{
		putlog_fd("%s\n", envv[i]);
		i++
	}
}