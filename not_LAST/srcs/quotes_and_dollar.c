/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:28 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:25:29 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	quot_file(t_pipes *list, t_data *data, char redrct)
{
	t_files	*q;
	char	*save;

	q = NULL;
	save = NULL;
	if (redrct == '<')
		q = list->infile;
	else if (redrct == '>')
		q = list->outfile;
	while (q != NULL)
	{
		save = q->filename;
		q->filename = handling_quotes(&(*data), save);
		q = q->next;
	}
}

void	quotes_and_dollar(t_data *data)
{
	t_pipes	*p;
	char	*save;
	int		i;

	save = NULL;
	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		if (p->cmd_argv)
		{
			while (p->cmd_argv[i])
			{
				save = p->cmd_argv[i];
				p->cmd_argv[i] = handling_quotes(&(*data), save);
				i++;
			}
		}
		if (p->infile)
			quot_file(p, &(*data), '<');
		if (p->outfile)
			quot_file(p, &(*data), '>');
		p = p->next;
	}
}
