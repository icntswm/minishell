#include "minishell.h"

int	ft_pwd(char **cmd)
{
	char	*buf;

	buf = NULL;
	if (cmd[1] != 0 && cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell does not support options for pwd.\n", 2);
		make_heredoc_question_error(2);
		return (2);
	}
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		perror("Error");
		return (errno);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
	make_heredoc_question_error(0);
	return (0);
}
