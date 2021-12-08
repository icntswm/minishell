# include "minishell.h"

t_pipes *list_pipe(t_pipes *list, char *str)
{
	t_pipes *p;
	t_pipes *new_list;
	void *save;

	p = list;
	if (!p)
	{
		p = (t_pipes *)malloc(sizeof(t_pipes));
		p->cmd = str;
		p->cmd_argv = NULL;
		p->infile = NULL;
		p->pos_inred = NULL;
        p->outfile = NULL;
		p->pos_outred = NULL;
		p->next = NULL;
	}
	else
	{
		save = p;
		new_list = (t_pipes *)malloc(sizeof(t_pipes));
		while (p->next != NULL)
			p = p->next;
		p->next = new_list;
		p = save;
		new_list->cmd = str;
		new_list->cmd_argv = NULL;
		new_list->infile = NULL;
		new_list->pos_inred = NULL;
        new_list->outfile = NULL;
		new_list->pos_outred = NULL;
		new_list->next = NULL;
	}
	return (p);
}

void	remove_spaces_pipe(t_data *data)
{
	t_pipes *p;
	char *save;
	int check_empty_pipe;

	p = data->pipes;
	check_empty_pipe = 0;
	while (p != NULL)
	{
		save = p->cmd;
		p->cmd = ft_chartrim(save, ' ');
		free(save);
        if (p->cmd[0] == '\0' && data->col_pipes == 0)
            data->error = ft_strdup("nothing...");
		if (p->cmd[0] == '\0')
			check_empty_pipe++;
		p = p->next;
	}
	if (check_empty_pipe > 1)
		ft_error(&(*data), "pipe");
}

void	cut_pipe(t_data *data)
{
	t_pos	*p;
	int		i;
	int		start;

	i = 0;
	start = 0;
	p = data->pos_pipe;
	if (data->col_pipes == 0)
		data->pipes = list_pipe(data->pipes, ft_substr(data->line, 0, ft_strlen(data->line)));
	else
	{
		while (p != NULL)
		{
			data->pipes = list_pipe(data->pipes, ft_substr(data->line, start, p->pos - start));
			start = p->pos + 1;
			p = p->next;
			if (p == NULL)
				data->pipes = list_pipe(data->pipes, ft_substr(data->line, start, ft_strlen(data->line) - start));
		}
	}
}