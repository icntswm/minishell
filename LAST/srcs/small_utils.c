/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:24:52 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/24 18:09:48 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_slash_fork(int status)
{
	status++;
	printf("Quit\n");
}

int	check_ctrl_return(int status)
{
	if (status == 3)
		return (131);
	return (130);
}

int	search_slash_n(char *array)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (i < ft_strlen(array))
	{
		if (array[i] == '\n')
			col++;
		i++;
	}
	return (col);
}

void	make_heredoc_fork(t_pipes *p)
{
	while (p != NULL)
	{
		if (p->infile)
			make_red_here_file(p->infile, p->num);
		p = p->next;
	}
	exit (0);
}

int	check_double_redirect(t_data *data)
{
	t_pipes	*p;
	t_files	*q;

	p = data->pipes;
	while (p != NULL)
	{
		q = p->infile;
		while (q != NULL)
		{
			if (q->mode == 2)
				return (1);
			q = q->next;
		}
		p = p->next;
	}
	return (0);
}
