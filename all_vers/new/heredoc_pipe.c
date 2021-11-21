#include "minishell.h"

int	check_pipe_herdoc(t_data *data)
{
	t_pipes *p;
	int counter;

	counter = 0;
	p = data->pipes;
	while (p != NULL)
	{
		if (p->cmd[0] == '\0')
			counter++;
		p = p->next;
	}
	if (counter == 1 && data->col_pipes > 0)
		data->line = readline("> ");
	return(counter);
}

int		help_heredor_pipe(t_data *data, char **save_line)
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
			if (check_pipe_herdoc(&(*data)) == 0)
				return (0);
		}
	}
	return (1);
}

void	heredoc_pipe(t_data *data)
{
	char *save_line;
	char *new_line;

	save_line = data->line;
	if (check_pipe_herdoc(&(*data)) == 1)
	{
		while (data->error == NULL)
		{
			new_line = ft_strjoin(save_line, data->line);
			free(data->line);
			free(save_line);
			cleaning_pipe(data->pipes);
			cleaning_position_pipe(data->pos_pipe);
			data->col_pipes = 0;
			data->pos_pipe = NULL;
			data->pipes = NULL;
			data->line = new_line;
			remove_spaces_in_line(&(*data));
			search_pipe_position(&(*data));
			check_space_numfile(&(*data));
			if (help_heredor_pipe(&(*data), &save_line) == 0)
				break ;
		}
	}
}