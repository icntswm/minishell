#	include "minishell.h"

void	list_position_second(t_pos *p, int pos, int redirect)
{
	t_pos	*new_list;
	void	*save;

	save = p;
	new_list = (t_pos *)malloc(sizeof(t_pos));
	if (!new_list)
		error_malloc(1);
	while (p->next != NULL)
		p = p->next;
	p->next = new_list;
	p = save;
	new_list->pos = pos;
	new_list->red = redirect;
	new_list->next = NULL;
}

t_pos	*list_position(t_pos *list, int pos, int redirect)
{
	t_pos	*p;

	p = list;
	if (p == NULL)
	{
		p = (t_pos *)malloc(sizeof(t_pos));
		if (!p)
			error_malloc(1);
		p->pos = pos;
		p->red = redirect;
		p->next = NULL;
	}
	else
		list_position_second(p, pos, redirect);
	return (p);
}

int	skip_quotes(char *str, int quotes, int i)
{
	while (str[i])
	{
		i++;
		if (str[i] == quotes)
			return (i);
		else if (str[i] == '\0')
			return (-1);
	}
	return (i);
}

void	search_pipe_position(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(data->line))
	{
		if (data->line[i] == '>' && data->line[i + 1] == '|')
			i++;
		else if (data->line[i] == '|')
		{
			data->col_pipes++;
			data->pos_pipe = list_position(data->pos_pipe, i, 0);
		}
		else if (data->line[i] == 34)
			i = skip_quotes(data->line, 34, i);
		else if (data->line[i] == 39)
			i = skip_quotes(data->line, 39, i);
		if (i == -1)
		{
			ft_error(&(*data), "quotes");
			break ;
		}
		i++;
	}
}
