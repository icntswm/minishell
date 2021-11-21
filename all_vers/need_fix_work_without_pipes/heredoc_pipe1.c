#	include "minishell.h"

int	check_pipe_herdoc(t_data *data, char **save_line)
{
	t_pipes	*p;
	int		counter;
	int		file;

	counter = 0;
	p = data->pipes;
	while (p != NULL)
	{
		if (p->cmd[0] == '\0')
			counter++;
		p = p->next;
	}
	if (counter == 1 && data->col_pipes > 0)
	{
		data->line = readline("> ");
		if (!data->line)
		{
			file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
			write(file, "syntax error: unexpected end of file",
				ft_strlen("syntax error: unexpected end of file"));
			close(file);
			return (0);
		}
	}
	return (counter);
}

int	help_heredor_pipe(t_data *data, char **save_line)
{
	if (data->error == NULL)
	{
		cut_pipe(&(*data));
		remove_spaces_pipe(&(*data));
		check_inredirect(&(*data));
		if (data->error == NULL)
			check_outredirect(&(*data));
		if (data->error == NULL)
		{
			*save_line = data->line;
			if (check_pipe_herdoc(&(*data), &(*save_line)) == 0)
				return (0);
		}
	}
	return (1);
}

void	heredoc_pipe_make_file(t_data *data)
{
	int	file;

	if (data->line && !data->error)
	{
		file = open("heredoc_pipe", O_CREAT | O_TRUNC | O_RDWR, 0644);
		write(file, data->line, ft_strlen(data->line));
		close(file);
	}
	else if (data->error)
	{
		file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
		write(file, data->error, ft_strlen(data->error));
		free(data->error);
		close(file);
	}
	free(data->line);
	cleaning_pipe(data->pipes);
	cleaning_position_pipe(data->pos_pipe);
}

void	heredoc_pipe_proccess(t_data *data, char **save_line)
{
	char	*new_line;

	new_line = NULL;
	while (data->error == NULL)
	{
		new_line = ft_strjoin(*save_line, data->line);
		free(data->line);
		free(*save_line);
		cleaning_position_pipe(data->pos_pipe);
		cleaning_pipe(data->pipes);
		data->col_pipes = 0;
		data->pos_pipe = NULL;
		data->pipes = NULL;
		data->line = new_line;
		remove_spaces_in_line(&(*data));
		search_pipe_position(&(*data));
		check_space_numfile(&(*data));
		if (help_heredor_pipe(&(*data), &(*save_line)) == 0)
			break ;
	}
	heredoc_pipe_make_file(&(*data));
	exit(0);
}

void	heredoc_pipe(t_data *data)
{
	char	*save_line;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (search_pipe_herdoc(&(*data)) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			save_line = data->line;
			signal(SIGINT, ctrl_c_pipe_heredoc);
			if (check_pipe_herdoc(&(*data), &save_line) == 1)
				heredoc_pipe_proccess(&(*data), &save_line);
		}
		else if (pid > 0)
			wait (0);
		if (pid == 0)
			exit (0);
		signal(SIGINT, ctrl_c);
	}
}
