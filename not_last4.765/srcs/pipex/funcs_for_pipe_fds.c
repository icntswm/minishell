/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_for_pipe_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:15 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/25 19:09:01 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_fds(int number_of_pipes)
{
	int	**fd;
	int	i;

	fd = malloc((number_of_pipes) * (sizeof(int *)));
	if (!fd)
		return (NULL);
	i = 0;
	while (i < (number_of_pipes))
	{
		fd[i] = malloc(2 * (sizeof(int)));
		if (!fd[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i < number_of_pipes)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("Pipe error.\n", 2);
			return (NULL);
		}
		i++;
	}
	return (fd);
}

void	close_fds(int number_of_pipes, int **fd)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fds(int number_of_pipes, int **fd)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
