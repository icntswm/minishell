/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:21 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/23 15:13:32 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	list_pipe_second(t_pipes *p, char *str, int num)
{
	t_pipes	*new_list;
	void	*save;

	save = p;
	new_list = (t_pipes *)malloc(sizeof(t_pipes));
	if (!new_list)
		error_malloc(1);
	while (p->next != NULL)
		p = p->next;
	p->next = new_list;
	p = save;
	new_list->num = num;
	new_list->cmd = str;
	new_list->cmd_argv = NULL;
	new_list->infile = NULL;
	new_list->pos_inred = NULL;
	new_list->outfile = NULL;
	new_list->pos_outred = NULL;
	new_list->next = NULL;
}

t_pipes	*list_pipe(t_pipes *list, char *str, int num)
{
	t_pipes	*p;

	p = list;
	if (!p)
	{
		p = (t_pipes *)malloc(sizeof(t_pipes));
		if (!p)
			error_malloc(1);
		p->num = num;
		p->cmd = str;
		p->cmd_argv = NULL;
		p->infile = NULL;
		p->pos_inred = NULL;
		p->outfile = NULL;
		p->pos_outred = NULL;
		p->next = NULL;
	}
	else
		list_pipe_second(p, str, num);
	return (p);
}

void	remove_spaces_pipe(t_data *data)
{
	t_pipes	*p;
	char	*save;
	int		check_empty_pipe;

	p = data->pipes;
	check_empty_pipe = 0;
	while (p != NULL)
	{
		save = p->cmd;
		p->cmd = ft_chartrim(save, ' ');
		free(save);
		if (p->cmd[0] == '\0')
		{
			check_empty_pipe++;
			if (p->next == NULL)
				check_empty_pipe--;
		}
		p = p->next;
	}
	if (check_empty_pipe > 0)
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
		data->pipes = list_pipe(data->pipes, ft_substr(data->line, 0,
					ft_strlen(data->line)), i);
	else
	{
		while (p != NULL)
		{
			data->pipes = list_pipe(data->pipes,
					ft_substr(data->line, start, p->pos - start), i);
			i++;
			start = p->pos + 1;
			p = p->next;
			if (p == NULL)
				data->pipes = list_pipe(data->pipes, ft_substr(data->line,
							start, ft_strlen(data->line) - start), i);
		}
	}
}
