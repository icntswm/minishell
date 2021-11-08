#include "minishell.h"

static int	is_al_num(char *str)
{
	if (*str == '-')
	{
		str++;
		if (*str < '0' || *str > '9')
			str--;
		else
		{
			while (*str)
			{
				if (*str < '0' || *str > '9')
					return (0);
				str++;
			}
			return (2);
		}
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	help_exit1(char **cmd)
{
	if ((LLONG_MAX) - (ft_atoi(cmd[1]) * -1) + 2 > 0)
	{
		make_heredoc_question_error(2);
		exit(2);
	}
	else if ((ft_atoi(cmd[1]) % 256) > 255)
	{
		make_heredoc_question_error(2);
		exit(2);
	}
	else
	{
		make_heredoc_question_error(ft_atoi(cmd[1]) % 256);
		exit(ft_atoi(cmd[1]) % 256);
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

int	help_exit2(char **cmd)
{
	if ((LLONG_MIN) + (ft_atoi(cmd[1])) < 0)
	{
		make_heredoc_question_error(2);
		exit(2);
	}
	else if (((ft_atoi(cmd[1]) * -1) % 256) > 255)
	{
		make_heredoc_question_error(2);
		exit(2);
	}
	else
	{
		if ((256 - ((ft_atoi(cmd[1]) * -1) % 256)) == 256)
		{
			make_heredoc_question_error(0);
			exit (0);
		}
		else
		{
			make_heredoc_question_error(256 - ((ft_atoi(cmd[1]) * -1) % 256));
			exit(256 - ((ft_atoi(cmd[1]) * -1) % 256));
		}
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

int	ft_exit(char **cmd)
{
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	if (is_al_num(cmd[1]) == 1)
	{
		if (cmd[2] == NULL)
			if (help_exit1(cmd) == 1)
				return (1);
	}
	else if (is_al_num(cmd[1]) == 2)
	{
		if (cmd[2] == NULL)
			if (help_exit2(cmd) == 1)
				return (1);
	}
	else if (is_al_num(cmd[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(2);
	}
	return (0);
}
