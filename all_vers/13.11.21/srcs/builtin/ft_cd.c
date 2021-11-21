/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:15 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:18:15 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home_dir(t_envp *env)
{
	char	*str;
	char	*temp;

	while (env)
	{
		if (ft_strncmp(env->var, "HOME=", 5) == 0)
		{
			temp = ft_strchr(env->var, '=');
			temp++;
			str = ft_strdup(temp);
			return (str);
		}
		env = env->next;
	}
	write(2, "minishell: cd: HOME variable value not found.\n", 46);
	return (NULL);
}

static int	no_args_cd(t_data *data, char *pwd_buf, char ***envp)
{
	char	*home;
	char	*cwd;
	int		status;

	home = find_home_dir(data->env);
	if (!home)
		return (1);
	if (chdir(home) == -1)
	{
		perror("minishell");
		free(home);
		return (1);
	}
	free(home);
	cwd = getcwd(pwd_buf, 0);
	status = export_str(data, "PWD", cwd, envp);
	if (cwd)
		free(cwd);
	return (status);
}

int	help_cd(t_data *data, char **cmd, char *pwd_buf, char ***envp)
{
	char	*cwd;
	int		status;

	status = 0;
	cwd = NULL;
	if (chdir(cmd[1]) == -1)
		perror("minishell");
	else
	{
		cwd = getcwd(pwd_buf, 0);
		status = export_str(data, "PWD", cwd, envp);
		if (cwd)
			free(cwd);
	}
	return (status);
}

int	ft_cd(t_data *data, char **cmd, char ***envp)
{
	char	*pwd_buf;
	int		status;

	status = 0;
	pwd_buf = NULL;
	if (cmd[1] == NULL)
		status = no_args_cd(data, pwd_buf, envp);
	else if (cmd[1] != NULL && cmd[2] != NULL)
		ft_putstr_fd("minishell: too many arguments for cd.\n", 2);
	else
		status = help_cd(data, cmd, pwd_buf, envp);
	if (pwd_buf)
		free(pwd_buf);
	if (status)
		return (status);
	return (errno);
}
