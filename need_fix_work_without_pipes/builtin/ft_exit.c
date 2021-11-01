#include "../minishell.h"

static int	is_al_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(t_data *data, char **cmd)
{
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	if (is_al_num(cmd[1]))
	{
		if (cmd[2] == NULL)
			exit(ft_atoi(cmd[1]) % 256);
		ft_putstr_fd("Too many arguments for exit.\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("Not numeric argument.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}