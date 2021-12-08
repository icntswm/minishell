#include "minishell.h"

char	*make_filename(int i)
{
	char	*num;
	char	*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("heredoc", num);
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

void	check_status1(int status, int i, t_data *data)
{
	int		file;
	char	*str;

	file = open("quest_error", O_RDONLY, 0644);
	if (file != -1)
	{
		get_next_line(file, &str);
		close(file);
		if (status > 255 && i - 1 != data->col_pipes && ft_atoi(str) != 127)
			make_heredoc_question_error(1);
		free(str);
	}
}

void	check_status2(int status)
{
	int		file;
	char	*str;

	file = open("quest_error", O_RDONLY, 0644);
	if (file != -1)
	{
		get_next_line(file, &str);
		close(file);
		if (status == 0)
			make_heredoc_question_error(0);
		else if (status == 512 && ft_atoi(str) != -111)
			make_heredoc_question_error(2);
		else if (ft_atoi(str) != 127)
			make_heredoc_question_error(1);
		free(str);
	}
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
	{
		waitpid(pid[i++], &status, 0);
		check_status1(status, i, data);
	}
	signal(SIGINT, ctrl_c);
	check_status2(status);
	unlink_here_doc_files(data);
	free_fds(data->col_pipes, fd);
	free(pid);
	return (status);
}
