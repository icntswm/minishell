/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multipipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:22 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:30:32 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dupping_if_elses(int id[2], int i, int col, int **fd)
{
	if (i == col)
	{
		if (id[0] != 0)
			dup2(id[0], 0);
		else
			dup2(fd[i - 1][0], 0);
		if (id[1] != 0)
			dup2(id[1], 1);
	}
	else
	{
		if (id[0] != 0)
			dup2(id[0], 0);
		else
			dup2(fd[i - 1][0], 0);
		if (id[1] != 0)
			dup2(id[1], 1);
		else
			dup2(fd[i][1], 1);
	}
	return (0);
}

static int	dupping(t_data *data, int i, int **fd)
{
	int	id[2];

	id[0] = get_in_fd(data, i);
	id[1] = get_out_fd(data, i);
	if (i == 0)
	{
		if (id[0] != 0)
			dup2(id[0], 0);
		if (id[1] != 0)
			dup2(id[1], 1);
		else
			dup2(fd[i][1], 1);
	}
	else
		dupping_if_elses(id, i, data->col_pipes, fd);
	close_fds(data->col_pipes, fd);
	if (id[0])
		close(id[0]);
	if (id[1])
		close(id[1]);
	return (0);
}

static int	child_process(t_data *data, char ***envp, int i, int **fd)
{
	char	**cmd;
	t_pipes	*p_temp;
	int		j;

	p_temp = data->pipes;
	j = i;
	while (j--)
		p_temp = p_temp->next;
	cmd = get_exec_arguments(*envp, p_temp->cmd_argv);
	if (!cmd && !(p_temp->infile || p_temp->outfile))
		exit(127);
	dupping(data, i, fd);
	if (is_built_in(data, cmd, envp) == -1)
	{
		if (cmd != NULL)
		{
			execve(cmd[0], cmd, *envp);
			exit (1);
		}
		else
			exit (0);
	}
	return (0);
}

int	handle_multipipes(t_data *data, char ***envp, int **fd, int *pid)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < data->col_pipes + 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			signal(SIGINT, ctrl_c_fork);
			child_process(data, envp, i, fd);
		}
		else if (pid[i] < 0)
			exit(EXIT_FAILURE);
		i++;
	}
	return (0);
}
