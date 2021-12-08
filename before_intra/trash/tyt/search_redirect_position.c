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
		if (redrct == '>' && str[i - 1] != redrct && str[i - 1] != '<' && str[i - 1] != redrct && str[i] == redrct && str[i + 1] != redrct)
			p = list_position(p, i, 1);
		else if (redrct == '<' && str[i - 1] != redrct && str[i] == redrct && str[i + 1] != redrct)
			p = list_position(p, i, 1);
		else if (redrct == '>' && str[i - 1] == '<' && str[i] == '>')
			p = list_position(p, i, 12);
		else if (str[i - 1] != redrct && str[i] == redrct && str[i + 1] == redrct && str[i + 2] != redrct)
			p = list_position(p, ++i, 2);
	}
	return (p);
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
		while (i < ft_strlen(p->cmd))
		{
			if (p->cmd[i] == 34)
				i = skip_quotes(p->cmd, 34, i);
			else if (p->cmd[i] == 39)
				i = skip_quotes(p->cmd, 39, i);
			else if (redrct == '>' && p->cmd[i] == '>')
				q = help_position_file(q, p->cmd, i, redrct);
			else if (redrct == '<' && p->cmd[i] == '<' && p->cmd[i + 1] != '>')
				q = help_position_file(q, p->cmd, i, redrct);
			i++;
		}
		if (redrct == '<')
			p->pos_inred = q;
		else
			p->pos_outred = q;
		p = p->next;
	}
}
