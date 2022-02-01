#include "minishell.h"

int	is_built_in(t_data *data, char **cmd, char ***envp)
{
	if (cmd != NULL && ft_strncmp(cmd[0], "echo", 5) == 0)
		exit(ft_echo(cmd));
	if (cmd != NULL && ft_strncmp(cmd[0], "pwd", 4) == 0)
		exit(ft_pwd(cmd));
	if (cmd != NULL && ft_strncmp(cmd[0], "cd", 3) == 0)
		exit(ft_cd(data, cmd, envp));
	if (cmd != NULL && ft_strncmp(cmd[0], "export", 7) == 0)
		exit(ft_export(data, cmd, envp));
	if (cmd != NULL && ft_strncmp(cmd[0], "unset", 6) == 0)
		exit(ft_unset(data, cmd, envp));
	if (cmd != NULL && ft_strncmp(cmd[0], "env", 4) == 0)
		exit(ft_env(data, cmd));
	if (cmd != NULL && ft_strncmp(cmd[0], "exit", 5) == 0)
		exit(ft_exit(data, cmd));
	return (-1);
}

int	check_built_in(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", 5) == 0) || \
			(ft_strncmp(cmd, "pwd", 4) == 0) || \
			(ft_strncmp(cmd, "cd", 3) == 0) || \
			(ft_strncmp(cmd, "export", 7) == 0) || \
			(ft_strncmp(cmd, "unset", 6) == 0) || \
			(ft_strncmp(cmd, "env", 4) == 0) || \
			(ft_strncmp(cmd, "exit", 5) == 0))
		return (1);
	return (0);
}
