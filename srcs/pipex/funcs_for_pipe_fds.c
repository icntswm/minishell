#include "minishell.h"

int	**close_and_free_fds(int **fd, int i, int pipes_num)
{
	int	j;

	j = 0;
	i--;
	while (i >= 0)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i--;
	}
	while (j < pipes_num)
	{
		free(fd[j]);
		j++;
	}
	free(fd);
	return (NULL);
}

int	help_make_fds(int i, int number_of_pipes, int **fd)
{
	while (i < (number_of_pipes))
	{
		fd[i] = malloc(2 * (sizeof(int)));
		if (!fd[i])
		{
			i--;
			while (i >= 0)
			{
				free(fd[i]);
				i--;
			}
			free(fd);
			return (2);
		}
		i++;
	}
	return (0);
}

int	**make_fds(int number_of_pipes)
{
	int	**fd;
	int	i;

	fd = malloc((number_of_pipes) * (sizeof(int *)));
	if (!fd)
		return (NULL);
	i = 0;
	if (help_make_fds(i, number_of_pipes, fd))
		return (NULL);
	while (i < number_of_pipes)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("minishell: pipe error.\n", 2);
			return (close_and_free_fds(fd, i, number_of_pipes));
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
