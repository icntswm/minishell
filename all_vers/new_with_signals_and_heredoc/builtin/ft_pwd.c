#include "../minishell.h"

int	ft_pwd(char **cmd)
{
	char	*buf = NULL;

	if (cmd[1] != 0 && cmd[1][0] == '-')
	{
		ft_putstr_fd("Minishell does not support options for pwd.\n", 2);
		return (1);
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
	free_array(cmd);
	return (0);
}
