#include "minishell.h"

int help_inred(t_data *data, t_pipes *p, int i, int red)
{
	int save_pos;

	save_pos = i;
	while (p->cmd[i] && p->cmd[i] == ' ')
		i++;
	if (p->cmd[i] == '\0' && p->next == NULL)
		ft_error(&(*data), "newline");
	else if (p->cmd[i] == '\0' && p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] != '<' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<')
		ft_error(&(*data), "two_inred");
	else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>')
		ft_error(&(*data), "inout_red");
	else if (save_pos != i && p->cmd[i] == '>' && p->cmd[i + 1] != '|' && p->cmd[i + 1] != '>')
		ft_error(&(*data), "one_outred");
	else if (red == 2 && p->cmd[i] == '>' && p->cmd[i + 1] != '|' && p->cmd[i + 1] != '>')
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

void	check_inredirect(t_data *data)
{
	t_pipes *p;
	int i;

	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		if (p->cmd[i] == 34)
			i = skip_quotes(p->cmd, 34, i);
		else if (p->cmd[i] == 39)
			i = skip_quotes(p->cmd, 39, i);
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '\0' && p->next == NULL)
			ft_error(&(*data), "newline");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '\0' && p->next != NULL)
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '|' && p->cmd[i + 2] == '\0')
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '\0' && p->next == NULL)
			ft_error(&(*data), "newline");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '\0' && p->next != NULL)
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '|')
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>' && p->cmd[i + 2] == '\0' && p->next == NULL)
			ft_error(&(*data), "newline");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>' && p->cmd[i + 2] == '\0' && p->next != NULL)
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>' && p->cmd[i + 2] == '|')
			ft_error(&(*data), "pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '>' && p->cmd[i + 2] == '>' && p->cmd[i + 3] != '>')
			ft_error(&(*data), "one_outred");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '>' && p->cmd[i + 3] != '|')
			ft_error(&(*data), "one_outred");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '>' && p->cmd[i + 3] == '|')
			ft_error(&(*data), "red_pipe");
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == '>' && p->cmd[i + 2] == '>')
			ft_error(&(*data), "two_outred");
		 else if (p->cmd[i] == '<' && p->cmd[i + 1] == ' ')
		{
			i++;
			i = help_inred(&(*data), p, i, 1);
		}
		else if (p->cmd[i] == '<' && p->cmd[i + 1] == '<' && p->cmd[i + 2] == ' ')
		{
			i+=2;
			i = help_inred(&(*data), p, i, 2);
		}
		if (data->error != NULL)
			return ;
		else
		{
			if (p->cmd[0] == 34 || p->cmd[0] == 39)
				i = 0;
			else
				i = 1;
			while (i < ft_strlen(p->cmd))
			{
				if (p->cmd[i] == 34)
					i = skip_quotes(p->cmd, 34, i);
				else if (p->cmd[i] == 39)
					i = skip_quotes(p->cmd, 39, i);
				else if (p->cmd[i - 1] != '<' && p->cmd[i] == '<' && p->cmd[i + 1] != '<')
				{
					i++;
					i = help_inred(&(*data), p, i, 1);
				}
				else if (p->cmd[i - 1] != '<' && p->cmd[i] == '<' && p->cmd[i + 1] =='<' && p->cmd[i + 2] != '<')
				{
					i+=2;
					i = help_inred(&(*data), p, i, 2);
				}
				else if (p->cmd[i - 1] == '<' && p->cmd[i] == '<' && p->cmd[i + 1] == '<')
					ft_error(&(*data), "three_inred");
				if (data->error != NULL)
					return ;
				i++;
			}
		}
		p = p->next;
	}
}