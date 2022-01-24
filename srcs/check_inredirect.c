/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inredirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:13 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:14 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	help_check_inredirect1(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '|')
		ft_error(&(*data), "pipe");
	else if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '>'
		&& str[i + 3] != '>')
		ft_error(&(*data), "one_outred");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '>'
		&& str[i + 3] != '|')
		ft_error(&(*data), "one_outred");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '>'
		&& str[i + 3] == '|')
		ft_error(&(*data), "red_pipe");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '>'
		&& str[i + 2] == '>')
		ft_error(&(*data), "two_outred");
	else if (str[i] == '<' && str[i + 1] == ' ')
	{
		i++;
		i = help_inred(&(*data), p, i, 1);
	}
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == ' ')
	{
		i += 2;
		i = help_inred(&(*data), p, i, 2);
	}
}

void	check_inredirect1(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[i] == 34)
		i = skip_quotes(str, 34, i);
	else if (str[i] == 39)
		i = skip_quotes(str, 39, i);
	else if (str[i] == '<' && str[i + 1] == '\0' && p->next == NULL)
		ft_error(&(*data), "newline");
	else if ((str[i] == '<' && str[i + 1] == '\0' && p->next != NULL)
		|| (str[i] == '<' && str[i + 1] == '|' && str[i + 2] == '\0'))
		ft_error(&(*data), "pipe");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0'
		&& p->next == NULL)
		ft_error(&(*data), "newline");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0'
		&& p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '|')
		ft_error(&(*data), "pipe");
	else if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '\0'
		&& p->next == NULL)
		ft_error(&(*data), "newline");
	else if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '\0'
		&& p->next != NULL)
		ft_error(&(*data), "pipe");
	else
		help_check_inredirect1(&(*data), &(*p), str, i);
}

void	check_intedirect2(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[0] == 34 || str[0] == 39)
		i = 0;
	else
		i = 1;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == 34)
			i = skip_quotes(str, 34, i);
		else if (str[i] == 39)
			i = skip_quotes(str, 39, i);
		else if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] != '<')
			i = help_inred(&(*data), p, ++i, 1);
		else if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<'
			&& str[i + 2] != '<')
		{
			i += 2;
			i = help_inred(&(*data), p, i, 2);
		}
		else if (str[i - 1] == '<' && str[i] == '<' && str[i + 1] == '<')
			ft_error(&(*data), "three_inred");
		if (data->error != NULL)
			return ;
		i++;
	}
}

void	check_inredirect(t_data *data)
{
	t_pipes	*p;
	int		i;

	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		check_inredirect1(&(*data), p, p->cmd, i);
		if (data->error != NULL)
			return ;
		else
			check_intedirect2(&(*data), p, p->cmd, i);
		if (data->error != NULL)
			return ;
		p = p->next;
	}
}
