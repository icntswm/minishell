#include "../minishell.h"

int	**make_fds(int number_of_pipes)
{
	int	**fd;
	int	i;

	fd = malloc((number_of_pipes) * (sizeof(int *)));
	if (!fd)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < (number_of_pipes))
	{
		fd[i] = malloc(2 * (sizeof(int)));
		if (!fd[i])
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < number_of_pipes)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("Pipe error.\n", 2);
			exit(EXIT_FAILURE);
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
