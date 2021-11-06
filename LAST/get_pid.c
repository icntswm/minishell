/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:23:59 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:00 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_array2(char ***arr, char *array)
{
	int		i;
	int		col;
	int		start;
	int		end;
	char	**ar;

	i = 0;
	col = 0;
	start = 0;
	end = 0;
	while (i++ < ft_strlen(array))
		if (array[i] == '\n')
			col++;
	ar = (char **)malloc(sizeof(char *) * (col + 1));
	i = 0;
	while (i < col)
	{
		while (array[end] && array[end] != '\n')
			end++;
		ar[i++] = ft_substr(array, start, end - start);
		start = end + 1;
		end++;
	}
	ar[i] = '\0';
	*arr = ar;
}

void	make_array(char ***arr)
{
	char	*str;
	char	*array;
	int		file;
	char	*save;

	str = NULL;
	save = NULL;
	array = NULL;
	file = open("user_getpid", O_RDONLY, 0644);
	while (get_next_line(file, &str))
	{
		save = array;
		array = ft_strjoin(save, str);
		free(save);
		save = array;
		array = ft_strjoin(save, "\n");
		free(save);
		free(str);
	}
	free(str);
	close(file);
	unlink("user_getpid");
	make_array2(arr, array);
	free(array);
}

void	cleaning_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	init_get_pid(t_data *data, char **arr_cmd, char **arr_pid)
{
	int	j;
	int	i;
	int	check;

	j = 0;
	check = 0;
	while (arr_cmd[j])
	{
		i = 0;
		while (arr_cmd[j][i])
		{
			if (arr_cmd[j][i] == '.' && arr_cmd[j][i + 1] == '/'
				&& arr_cmd[j][i + 2] == 'm')
				check = j;
			i++;
		}
		j++;
	}
	data->get_pid = ft_atoi(arr_pid[check]);
	cleaning_arr(arr_cmd);
	cleaning_arr(arr_pid);
}

void	get_pid1(char ***arr, char **envp, char *arg)
{
	char	**ps;
	int		file;
	pid_t	pid;

	ps = (char **)malloc(sizeof(char *) * 4);
	ps[0] = ft_strdup("ps");
	ps[1] = ft_strdup("-o");
	ps[2] = ft_strdup(arg);
	ps[3] = NULL;
	pid = fork();
	if (pid == 0)
	{
		file = open("user_getpid", O_CREAT | O_TRUNC | O_RDWR, 0644);
		dup2(file, 1);
		close(file);
		execve("/bin/ps", ps, envp);
	}
	else
		wait (0);
	if (pid == 0)
		exit (0);
	make_array(arr);
	cleaning_arr(ps);
}

void	get_pid(t_data *data, char **envp)
{
	char	**arr_pid;
	char	**arr_cmd;

	arr_pid = NULL;
	arr_cmd = NULL;
	if (access("/bin/ps", 0) == 0)
	{
		get_pid1(&arr_pid, envp, "pid");
		get_pid1(&arr_cmd, envp, "command");
	}
	init_get_pid(&(*data), arr_cmd, arr_pid);
}
