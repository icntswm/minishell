/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:48 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/26 18:44:14 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
	{
		free(arr[count]);
		count++;
	}
	free(arr);
}

static char	**find_pathes(char *envp[])
{
	char	*path_str;
	char	**pathes;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			path_str = *envp;
			break ;
		}
		envp++;
	}
	if (!*envp)
		return (NULL);
	path_str = ft_strchr(path_str, '/');
	pathes = ftt_split(path_str, ':');
	if (!pathes)
		return (NULL);
	return (pathes);
}

static char	*get_path_str(char *cmd, char **pathes)
{
	char	*path;
	char	*temp;

	if (!cmd)
		return (NULL);
	while (*pathes)
	{
		temp = ft_strjoin(*pathes, "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		pathes++;
	}
	return (NULL);
}

static char	*get_path(char **cmd_args, char *envp[])
{
	char	**pathes;
	char	*path;

	if (access(cmd_args[0], X_OK) != -1)
	{
		path = ft_strdup(cmd_args[0]);
		if (!path)
			return (NULL);
		return (path);
	}
	pathes = find_pathes(envp);
	if (!pathes)
	{
		ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd_args[0], 2), \
		write(2, ": command not found.\n", 21);
		return (NULL);
	}
	path = get_path_str(cmd_args[0], pathes);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd_args[0], 2), \
		write(2, ": command not found.\n", 21), free_array(pathes);
		return (NULL);
	}
	free_array(pathes);
	return (path);
}

char	**get_exec_arguments(char *envp[], char **cmd_args)
{
	char	*path;

	if (cmd_args && *cmd_args)
	{
		if (check_built_in(cmd_args[0]) != 0)
			return (cmd_args);
		path = get_path(cmd_args, envp);
		if (!path)
		{
			free_array(cmd_args);
			return (NULL);
		}
		free(cmd_args[0]);
		cmd_args[0] = path;
		return (cmd_args);
	}
	return (NULL);
}
