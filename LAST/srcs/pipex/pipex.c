/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:24 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:31:20 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_filename(int i)
{
	char	*num;
	char	*filename;

	num = ft_itoa(i);
	filename = ft_strjoin(".heredoc", num);
	free(num);
	return (filename);
}

int	unlink_here_doc_files(t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	while (i <= data->col_pipes)
	{
		name = make_filename(i);
		if (access(name, F_OK) == 0)
		{
			if (unlink(name) == -1)
			{
				perror("Unlink error");
				free(name);
				return (1);
			}
		}
		free(name);
		i++;
	}
	return (0);
}

int	pipex(t_data *data, char ***envp)
{
	int		**fd;
	pid_t	*pid;
	int		i;
	int		status;

	if (data->col_pipes == 0)
		return (work_without_pipes(data, envp));
	fd = make_fds(data->col_pipes);
	pid = malloc((data->col_pipes + 1) * sizeof(pid_t *));
	if (!pid)
		exit(EXIT_FAILURE);
	handle_multipipes(data, envp, fd, pid);
	close_fds(data->col_pipes, fd);
	i = 0;
	while (i < data->col_pipes + 1)
		waitpid(pid[i++], &status, 0);
	signal(SIGINT, ctrl_c);
	unlink_here_doc_files(data);
	free_fds(data->col_pipes, fd);
	free(pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (130);
}
