#include "minishell.h"

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
