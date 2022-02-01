#include "minishell.h"

void	list_file_second(t_files *p, char *str, int redirect)
{
	t_files	*new_list;
	void	*save;

	save = p;
	new_list = (t_files *)malloc(sizeof(t_files));
	if (!new_list)
		error_malloc(1);
	while (p->next != NULL)
		p = p->next;
	p->next = new_list;
	p = save;
	new_list->filename = str;
	new_list->mode = redirect;
	new_list->next = NULL;
}

t_files	*list_file(t_files *list, char *str, int redirect)
{
	t_files	*p;

	p = list;
	if (!p)
	{
		p = (t_files *)malloc(sizeof(t_files));
		if (!p)
			error_malloc(1);
		p->filename = str;
		p->mode = redirect;
		p->next = NULL;
	}
	else
		list_file_second(p, str, redirect);
	return (p);
}

int	end_file(char *str, int start, int len)
{
	int	end;
	int	save_start;

	end = len + start;
	save_start = start;
	while (str[start] && str[start] == ' ')
		start++;
	while (start < end)
	{
		if (str[start] == 34)
			start = skip_quotes(str, 34, start);
		else if (str[start] == 39)
			start = skip_quotes(str, 39, start);
		if (str[start] == '|')
		{
			start++;
			while (start < end && str[start] == ' ')
				start++;
		}
		if (str[start] == ' ' || str[start] == '>'
			|| str[start] == '<' || str[start] == '\0')
			break ;
		start++;
	}
	return (start - save_start);
}

t_files	*fill_list(t_pipes *pipes, char redrct)
{
	t_files	*p;
	t_pos	*q;

	if (redrct == '>')
	{
		p = pipes->outfile;
		q = pipes->pos_outred;
	}
	else
	{
		p = pipes->infile;
		q = pipes->pos_inred;
	}
	while (q != NULL)
	{
		if (q->next == NULL)
			p = list_file(p, ft_substr(pipes->cmd, q->pos + 1, end_file(\
	pipes->cmd, q->pos + 1, ft_strlen(pipes->cmd) - (q->pos + 1))), q->red);
		else
			p = list_file(p, ft_substr(pipes->cmd, q->pos + 1, end_file(\
	pipes->cmd, q->pos + 1, q->next->pos - (q->pos + 1))), q->red);
		q = q->next;
	}
	return (p);
}

void	make_list(t_data *data, char redrct)
{
	t_pipes	*p;

	p = data->pipes;
	if (redrct == '>')
	{
		while (p != NULL)
		{
			if (p->pos_outred)
				p->outfile = fill_list(p, redrct);
			p = p->next;
		}
	}
	else
	{
		while (p != NULL)
		{
			if (p->pos_inred)
				p->infile = fill_list(p, redrct);
			p = p->next;
		}
	}
}
