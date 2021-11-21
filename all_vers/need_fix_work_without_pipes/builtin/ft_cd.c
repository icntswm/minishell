#include "../minishell.h"

static char	*find_home_dir(t_envp *env)
{
	char	*str;
	char	*temp;

	while (env)
	{
		if (ft_strncmp(env->var, "HOME=", 5) == 0)
		{
			temp = ft_strchr(env->var, '='), temp++;
			str = ft_strdup(temp);
			return (str);
		}
		env = env->next;
	}
	write(2, "minishell: cd: HOME variable value not found.\n", 46);
	return (NULL);
}

static int	no_args_cd(t_data *data, char **cmd, char *pwd_buf, char ***envp)
{
	char	*home;

	home = find_home_dir(data->env);
	if (!home)
	{
		free_array(cmd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("Error");
		free(home);
		return (1);
	}
	free(home);
	return (export_str(data, "PWD", getcwd(pwd_buf, 0), envp));
}

int	ft_cd(t_data *data, char **cmd, char ***envp)
{
	char	*pwd_buf;
	int		status;

	pwd_buf = NULL;
	if (cmd[1] == NULL)
		status = no_args_cd(data, cmd, pwd_buf, envp);
	else if (cmd[1] != NULL && cmd[2] != NULL)
		ft_putstr_fd("Too many arguments for cd.\n", 2);
	else
	{
		if (chdir(cmd[1]) == -1)
			perror("Error");
		else
			status = export_str(data, "PWD", getcwd(pwd_buf, 0), envp);
	}
	if (pwd_buf)
		free(pwd_buf);
	free_array(cmd);
	if (status)
		return (status);
	return (errno);
}
