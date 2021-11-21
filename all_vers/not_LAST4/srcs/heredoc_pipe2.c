/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:53 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/09 00:26:55 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	check_pipe_herdoc(t_data *data)
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
			return (0);
		}
	}
	return (counter);
}

int	search_pipe_herdoc(t_data *data)
{
	t_pipes	*p;
	int		counter;

	counter = 0;
	p = data->pipes;
	while (p != NULL)
	{
		if (p->cmd[0] == '\0' && data->col_pipes > 0)
			counter++;
		p = p->next;
	}
	return (counter);
}

void	have_heredoc_pipe(t_data *data, int file1)
{
	clean_position(data->pos_pipe);
	cleaning_all(data->pipes);
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
			if (search_pipe_herdoc(&(*data)) != 0 && data->col_pipes > 0
				&& data->line[ft_strlen(data->line) - 1] == '|'
				&& data->line[ft_strlen(data->line)] == '\0')
				data->error = ft_strdup("ctrl_c_pipe_heredoc");
		}
	}
	else
		have_heredoc_pipe(&(*data), file1);
}
