#include "minishell.h"

int	help_echo(char **cmd)
{
	if (*cmd && ft_strncmp(*cmd, "-n", 3) == 0)
	{
		cmd++;
		while (*cmd)
		{
			ft_putstr_fd(*cmd, 1);
			cmd++;
			if (*cmd != NULL)
				ft_putchar_fd(' ', 1);
		}
		make_heredoc_question_error(0);
		return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	// char	**temp_for_free;

	// temp_for_free = cmd;
	cmd++;
	if (*cmd && **cmd == '-' && *(*cmd + 1) != 'n')
	{
		ft_putstr_fd("Minishell supports only -n option for echo.\n", 2);
		make_heredoc_question_error(2);
		return (2);
	}
	if (help_echo(cmd) == 0)
		return (0);
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		ft_putchar_fd(' ', 1);
		cmd++;
	}
	ft_putchar_fd('\n', 1);
	// free_array(temp_for_free);
	make_heredoc_question_error(0);
	return (0);
}
