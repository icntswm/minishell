/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_without_pipes2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:29 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/12 17:38:50 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_pipes_dupping(t_data *data)
{
	int	in_id;
	int	out_id;

	in_id = get_in_fd(data, 0);
	out_id = get_out_fd(data, 0);
	if (in_id != 0)
		dup2(in_id, 0);
	if (out_id != 0)
		dup2(out_id, 1);
	if (in_id)
		close(in_id);
	if (out_id)
		close(out_id);
	return (0);
}

void	help_get_path(char **cmd_args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	write(2, ": command not found\n", 20);
}

int	is_there_slash(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	check_for_dir(char *cmd, char **path)
{
	struct stat	stat_info;

	if (is_there_slash(cmd))
	{
		stat(cmd, &stat_info);
		if (access(cmd, F_OK) == 0 && S_ISDIR(stat_info.st_mode))
		{
			ft_putstr_fd("minishell1: '", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': is a catalog\n", 2);
		}
		else if (access(cmd, X_OK) != -1)
		{
			*path = ft_strdup(cmd);
			return (2);
		}
		else
		{
			ft_putstr_fd("minishell: '", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': no such file or catalog\n", 2);
		}
		return (1);
	}
	return (0);
}
