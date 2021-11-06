/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutting_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:28 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:29 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

char	*help_cut_redirect(char *str, int i)
{
	char	*save1;
	char	*save2;
	char	*new;

	save1 = NULL;
	save2 = NULL;
	new = NULL;
	if (i == 0)
	{
		save2 = ft_substr(str, 1, ft_strlen(str));
		new = ft_strjoin(save1, save2);
		free(save2);
	}
	else
	{
		save1 = ft_substr(str, 0, i);
		save2 = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
		new = ft_strjoin(save1, save2);
		free(save1);
		free(save2);
	}
	free(str);
	return (new);
}

int	help_cutting_redirect(int check, int i)
{
	if (check == 1)
		i = 0;
	else
		i++;
	return (i);
}

void	cutting_redirect(t_data *data)
{
	t_pipes	*p;
	int		i;
	int		check;

	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		while (p->cmd[i])
		{
			check = 0;
			if (p->cmd[i] == 34)
				i = skip_quotes(p->cmd, 34, i);
			else if (p->cmd[i] == 39)
				i = skip_quotes(p->cmd, 39, i);
			else if (p->cmd[i] == '>' || p->cmd[i] == '<')
			{
				p->cmd = help_cut_redirect(p->cmd, i);
				check = 1;
			}
			i = help_cutting_redirect(check, i);
		}
		p = p->next;
	}
}
