/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_without_pipes1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:26 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/12 01:03:11 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in_dupping(t_data *data)
{
	int	in_id;
	int	out_id;

	in_id = get_in_fd(data, 0);
	out_id = get_out_fd(data, 0);
	if (in_id)
		close(in_id);
	if (out_id)
		close(out_id);
	return (0);
}

static int	check_built_in_cmd(t_data *data, char **cmd, char ***envp)
{
	int	ret;

	ret = -1;
	if ((ft_strncmp(cmd[0], "export", 7) == 0) && cmd[1])
	{
		built_in_dupping(data);
		ret = ft_export(data, cmd, envp);
	}
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
	{
		built_in_dupping(data);
		ret = ft_unset(data, cmd, envp);
	}
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		built_in_dupping(data);
		ret = ft_cd(data, cmd, envp);
	}
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		built_in_dupping(data);
		ret = ft_exit(cmd);
	}
	return (ret);
}

void	exec_process_help(t_data *data, char **cmd, char ***envp)
{
	if (is_built_in(data, cmd, envp) == -1)
	{
		if (cmd != NULL)
		{
			execve(cmd[0], cmd, *envp);
			exit (1);
		}
		else
			exit (1);
	}
}

static	int	exec_process(int pid, t_data *data, char **cmd, char ***envp)
{
	int	status;

	if (cmd != NULL && (ft_strncmp(cmd[0], \
		"./minishell", ft_strlen("./minishell")) == 0))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		signal(SIGINT, ctrl_c_fork);
	if (pid == 0)
	{
		no_pipes_dupping(data);
		if (!cmd)
			exit(127);
		exec_process_help(data, cmd, envp);
	}
	else if (pid < 0)
		return (errno);
	waitpid(pid, &status, 0);
	if (access(".heredoc0", F_OK) == 0)
		if (unlink(".heredoc0") == -1)
			perror("Unlink error");
	return (status);
}

int	work_without_pipes(t_data *data, char ***envp)
{
	char	**cmd;
	t_pipes	*p_temp;
	int		pid;
	int		ret;
	int		status;

	status = 0;
	p_temp = data->pipes;
	cmd = get_exec_arguments(*envp, p_temp->cmd_argv);
	if (cmd)
	{
		ret = check_built_in_cmd(data, cmd, envp);
		if (ret != -1)
			return (ret);
	}
	pid = fork();
	status = exec_process(pid, data, cmd, envp);
	signal(SIGINT, ctrl_c);
	unlink_here_doc_files(data);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (130);
}
