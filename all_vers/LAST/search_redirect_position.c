/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect_position.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:40 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:25:42 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pos	*help_position_file(t_pos *list, char*str, int i, char redrct)
{
	t_pos	*p;

	p = list;
	if (i == 0)
	{
		if (str[i + 1] != redrct)
			p = list_position(p, i, 1);
		else if (str[i + 1] == redrct && str[i + 2] != redrct)
			p = list_position(p, ++i, 2);
	}
	else if (i > 0)
	{
		if (redrct == '>' && str[i - 1] != redrct && str[i - 1] != '<'
			&& str[i - 1] != redrct && str[i] == redrct && str[i + 1] != redrct)
			p = list_position(p, i, 1);
		else if (redrct == '<' && str[i - 1] != redrct && str[i] == redrct
			&& str[i + 1] != redrct)
			p = list_position(p, i, 1);
		else if (redrct == '>' && str[i - 1] == '<' && str[i] == '>')
			p = list_position(p, i, 12);
		else if (str[i - 1] != redrct && str[i] == redrct
			&& str[i + 1] == redrct && str[i + 2] != redrct)
			p = list_position(p, ++i, 2);
	}
	return (p);
}

void	help_search_position(t_pos **q, char *str, char redrct)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == 34)
			i = skip_quotes(str, 34, i);
		else if (str[i] == 39)
			i = skip_quotes(str, 39, i);
		else if (redrct == '>' && str[i] == '>')
			*q = help_position_file(*q, str, i, redrct);
		else if (redrct == '<' && str[i] == '<' && str[i + 1] != '>')
			*q = help_position_file(*q, str, i, redrct);
		i++;
	}
}

void	search_redirect_position(t_data *data, char redrct)
{
	t_pipes	*p;
	t_pos	*q;
	int		i;

	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		if (redrct == '<')
			q = p->pos_inred;
		else
			q = p->pos_outred;
		help_search_position(&q, p->cmd, redrct);
		if (redrct == '<')
			p->pos_inred = q;
		else
			p->pos_outred = q;
		p = p->next;
	}
}
