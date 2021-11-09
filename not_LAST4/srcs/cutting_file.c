/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutting_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:25 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/09 00:09:03 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_in_cmd(char *new, char *str, int start, int len)
{
	char	*save_1;
	char	*save;

	save = new;
	if (str[start + len] == '>' && str[start + len - 1] == '<')
		len++;
	save_1 = ft_substr(str, start, len);
	new = ft_strjoin(save, save_1);
	free(save_1);
	free(save);
	return (new);
}

void	cut_file(t_pipes *p, char redrct)
{
	t_pos	*q;
	int		s;
	char	*new_cmd;

	s = 0;
	new_cmd = NULL;
	if (redrct == '<')
		q = p->pos_inred;
	else
		q = p->pos_outred;
	while (q != NULL)
	{
		new_cmd = cut_in_cmd(new_cmd, p->cmd, s - 1, q->pos - (s - 1));
		s = q->pos;
		q = q->next;
		if (q != NULL)
			s = s + 1 + end_file(p->cmd, s + 1, q->pos - s);
		else
			s = s + 2 + end_file(p->cmd, s + 2, ft_strlen(p->cmd) - (s + 1));
		s++;
	}
	if (q == NULL)
		new_cmd = cut_in_cmd(new_cmd, p->cmd, s, ft_strlen(p->cmd) - (s - 1));
	free(p->cmd);
	p->cmd = new_cmd;
}

t_pos	*clean_red(t_pos *list)
{
	t_pos	*p;
	void	*save;

	p = list;
	while (p != NULL)
	{
		save = p->next;
		free(p);
		p = save;
	}
	return (p);
}

void	cutting_file2(t_pipes *p)
{
	while (p != NULL)
	{
		if (p->pos_inred)
		{
			cut_file(p, '<');
			p->pos_inred = clean_red(p->pos_inred);
		}
		if (p->pos_outred)
			p->pos_outred = clean_red(p->pos_outred);
		p = p->next;
	}
}

void	cutting_file(t_data *data)
{
	t_pipes	*p;
	void	*save;

	p = data->pipes;
	save = p;
	while (p != NULL)
	{
		if (p->pos_outred)
		{
			cut_file(p, '>');
			p->pos_outred = clean_red(p->pos_outred);
		}
		if (p->pos_inred)
			p->pos_inred = clean_red(p->pos_inred);
		p = p->next;
	}
	search_redirect_position(&(*data), '<');
	p = save;
	cutting_file2(p);
}
