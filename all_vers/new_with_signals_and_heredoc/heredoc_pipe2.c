#	include "minishell.h"

int	search_pipe_herdoc(t_data *data)
{
	t_pipes	*p;
	int		counter;

	counter = 0;
	p = data->pipes;
	while (p != NULL)
	{
		if (p->cmd[0] == '\0')
			counter++;
		p = p->next;
	}
	return (counter);
}

void	have_heredoc_pipe(t_data *data, int file1)
{
	cleaning_position_pipe(data->pos_pipe);
	cleaning_pipe(data->pipes);
	data->col_pipes = 0;
	data->error = NULL;
	data->pos_pipe = NULL;
	data->pipes = NULL;
	free(data->line);
	get_next_line(file1, &data->line);
	unlink("heredoc_pipe");
	close(file1);
	remove_spaces_in_line(&(*data));
	search_pipe_position(&(*data));
	check_space_numfile(&(*data));
	if (data->error == NULL)
	{
		cut_pipe(&(*data));
		remove_spaces_pipe(&(*data));
	}
}

void	check_heredoc_file(t_data *data)
{
	int	file1;
	int	file2;

	file1 = open("heredoc_pipe", O_RDONLY, 0644);
	if (file1 == -1)
	{
		file2 = open("heredoc_error", O_RDONLY, 0644);
		if (file2 != -1)
		{
			get_next_line(file2, &data->error);
			unlink("heredoc_error");
			close(file2);
		}
		else
		{
			if (search_pipe_herdoc(&(*data)) != 0 && data->col_pipes > 0)
				data->error = ft_strdup("ctrl_c_pipe_heredoc");
		}
	}
	else
		have_heredoc_pipe(&(*data), file1);
}
