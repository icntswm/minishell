/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_out_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:08 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:09 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	help_inred1(t_data *data, t_pipes *p, int i, int red)
{
	if (red == 2 && p->cmd[i] == '>'
		&& p->cmd[i + 1] != '|' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_outred");
	else if (p->cmd[i - 1] == '<' && p->cmd[i] == '>' && p->cmd[i + 1] == '|')
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '>' && p->cmd[i + 1] == '|')
		ft_error(&(*data), "red_pipe");
	else if (p->cmd[i] == '>' && p->cmd[i + 1] == '>')
		ft_error(&(*data), "two_outred");
	else if (p->cmd[i] == '|')
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == 34 || p->cmd[i] == 39)
		i--;
	return (i);
}

int	help_inred(t_data *data, t_pipes *p, int i, int red)
{
	int	save_pos;

	save_pos = i;
	while (p->cmd[i] && p->cmd[i] == ' ')
		i++;
	if (p->cmd[i] == '\0' && p->next == NULL)
		ft_error(&(*data), "newline");
	else if (p->cmd[i] == '\0' && p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] != '<' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '<')
		ft_error(&(*data), "three_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<')
		ft_error(&(*data), "two_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>')
		ft_error(&(*data), "inout_red");
	else if (save_pos != i && p->cmd[i] == '>'
		&& p->cmd[i + 1] != '|' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_outred");
	else
		i = help_inred1(&(*data), p, i, red);
	return (i);
}

int	help_outred1(t_data *data, t_pipes *p, int i)
{
	if (p->cmd[i] == '|' && p->cmd[i + 1] == '\0'
		&& p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] != '<' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] != '<' && p->cmd[i + 1] == '>')
		ft_error(&(*data), "inout_red");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] != '<')
		ft_error(&(*data), "two_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '<')
		ft_error(&(*data), "three_inred");
	else if (p->cmd[i] == 34 || p->cmd[i] == 39)
		i--;
	return (i);
}

int	help_outred(t_data *data, t_pipes *p, int i, int red)
{
	int	save_pos;

	save_pos = i;
	while (p->cmd[i] && p->cmd[i] == ' ')
		i++;
	if (p->cmd[i] == '\0' && p->next == NULL)
		ft_error(&(*data), "newline");
	else if (p->cmd[i] == '\0' && p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '>' && p->cmd[i + 1] != '<' && p->cmd[i + 1] != '>'
		&& p->cmd[i + 1] != '|')
		ft_error(&(*data), "one_outred");
	else if (p->cmd[i] == '>' && p->cmd[i + 1] == '|')
		ft_error(&(*data), "red_pipe");
	else if (p->cmd[i] == '>' && p->cmd[i + 1] == '>')
		ft_error(&(*data), "two_outred");
	else if ((save_pos != i && p->cmd[i] == '|')
		|| (red == 2 && p->cmd[i] == '|'))
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '|' && p->cmd[i + 1] == '\0'
		&& p->next == NULL)
		ft_error(&(*data), "newline");
	else
		i = help_outred1(&(*data), p, i);
	return (i);
}
