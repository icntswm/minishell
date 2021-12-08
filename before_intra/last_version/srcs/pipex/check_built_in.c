/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:44:59 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/27 17:57:12 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_b_in_cmd(t_data *data, char **cmd)
{
	if (((ft_strncmp(cmd[0], "pwd", 4) == 0) && cmd[1])
		|| ((ft_strncmp(cmd[0], "env", 4) == 0) && cmd[1])
		|| ((ft_strncmp(cmd[0], "export", 7) == 0) && cmd[1])
		|| ((ft_strncmp(cmd[0], "echo", 5) == 0) && cmd[1])
		|| (ft_strncmp(cmd[0], "unset", 6) == 0)
		|| (ft_strncmp(cmd[0], "cd", 3) == 0))
	{
		if (built_in_dupping(data) == -1)
			return (-2);
		return (1);
	}
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		if (exit_dupping(data) == -1)
			return (-2);
		return (1);
	}
	return (0);
}

static int	check_b_in_cmd2(t_data *data, char **cmd, char ***envp)
{
	int	ret;

	ret = -1;
	if ((ft_strncmp(cmd[0], "pwd", 4) == 0) && cmd[1])
		ret = ft_pwd(cmd);
	else if ((ft_strncmp(cmd[0], "env", 4) == 0) && cmd[1])
		ret = ft_env(data, cmd);
	else if ((ft_strncmp(cmd[0], "export", 7) == 0) && cmd[1])
		ret = ft_export(data, cmd, envp);
	else if ((ft_strncmp(cmd[0], "echo", 5) == 0) && cmd[1])
		ret = ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ret = ft_unset(data, cmd, envp);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ret = ft_cd(data, cmd, envp);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		ret = ft_exit(data, cmd);
	}
	return (ret);
}

int	check_built_in_cmd(t_data *data, char **cmd, char ***envp)
{
	int	ret;
	int	ret2;
	int	temp1;
	int	temp2;

	temp1 = dup(0);
	temp2 = dup(1);
	ret = -1;
	ret2 = check_b_in_cmd(data, cmd);
	if (ret2 == 1)
		ret = check_b_in_cmd2(data, cmd, envp);
	else if (ret2 == -2)
		return (0);
	dup2(temp1, 0);
	dup2(temp2, 1);
	close(temp1);
	close(temp2);
	return (ret);
}
