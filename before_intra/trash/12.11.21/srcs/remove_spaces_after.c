/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:31 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:25:32 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	help_remove_space_file(t_pipes *list, char redrct)
{
	t_files	*q;
	char	*save;

	if (redrct == '<')
		q = list->infile;
	else
		q = list->outfile;
	while (q != NULL)
	{
		save = q->filename;
		q->filename = ft_chartrim(save, ' ');
		free(save);
		save = q->filename;
		q->filename = ft_chartrim(save, '|');
		free(save);
		save = q->filename;
		q->filename = ft_chartrim(save, ' ');
		free(save);
		q = q->next;
	}
}

void	remove_spaces_file(t_data *data)
{
	t_pipes	*p;

	p = data->pipes;
	while (p != NULL)
	{
		if (p->infile)
			help_remove_space_file(p, '<');
		if (p->outfile)
			help_remove_space_file(p, '>');
		p = p->next;
	}
}

void	remove_spaces_cmd(t_data *data)
{
	t_pipes	*p;
	char	*save;

	save = NULL;
	p = data->pipes;
	while (p != NULL)
	{
		save = p->cmd;
		p->cmd = ft_chartrim(save, ' ');
		free(save);
		p = p->next;
	}
}
