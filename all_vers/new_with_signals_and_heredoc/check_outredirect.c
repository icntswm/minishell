#	include "minishell.h"

void	help_check_outredirect1(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '<' && str[i + 2] == '<'
		&& str[i + 3] != '<')
		ft_error(&(*data), "two_inred");
	else if (str[i] == '>' && str[i + 1] == '<' && str[i + 2] == '<'
		&& str[i + 3] == '<')
		ft_error(&(*data), "three_inred");
	else if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<')
		|| (str[i] == '>' && str[i + 1] == '<'))
		ft_error(&(*data), "one_inred");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<'
		&& str[i + 3] != '<')
		ft_error(&(*data), "one_inred");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<'
		&& str[i + 3] == '<' && str[i + 4] != '<')
		ft_error(&(*data), "two_inred");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<'
		&& str[i + 3] == '<' && str[i + 4] == '<')
		ft_error(&(*data), "three_inred");
	else if (str[i] == '>' && str[i + 1] == ' ')
		i = help_outred(&(*data), p, ++i, 1);
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == ' ')
	{
		i += 2;
		i = help_outred(&(*data), p, i, 2);
	}
}

void	check_outredirect1(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[i] == 34)
		i = skip_quotes(str, 34, i);
	else if (str[i] == 39)
		i = skip_quotes(str, 39, i);
	else if (((str[i] == '>' && str[i + 1] == '\0') || (str[i] == '>'
				&& str[i + 1] == '>' && str[i + 2] == '\0')
			|| (str[i] == '>' && str[i + 1] == '|')) && p->next == NULL)
		ft_error(&(*data), "newline");
	else if ((str[i] == '>' && str[i + 1] == '\0' && p->next != NULL)
		|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '|'))
		ft_error(&(*data), "pipe");
	else if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
		&& p->next != NULL)
		ft_error(&(*data), "pipe");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'
		&& str[i + 3] != '>' && str[i + 3] != '|')
		ft_error(&(*data), "one_outred");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'
		&& str[i + 3] == '|')
		ft_error(&(*data), "red_pipe");
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'
		&& str[i + 3] == '>')
		ft_error(&(*data), "two_outred");
	else
		help_check_outredirect1(&(*data), &(*p), str, i);
}

void	check_outredirect2(t_data *data, t_pipes *p, char *str, int i)
{
	if (str[0] == 34 || str[0] == 39)
		i = 0;
	else
		i = 1;
	while (i < ft_strlen(str))
	{
		if (str[i] == 34)
			i = skip_quotes(str, 34, i);
		else if (str[i] == 39)
			i = skip_quotes(str, 39, i);
		else if (str[i - 1] != '>' && str[i] == '>' && str[i + 1] != '>')
			i = help_outred(&(*data), p, ++i, 1);
		else if (str[i - 1] != '>' && str[i] == '>' && str[i + 1] == '>'
			&& str[i + 2] != '>')
		{
			i += 2;
			i = help_outred(&(*data), p, i, 2);
		}
		else if (str[i - 1] == '>' && str[i] == '>' && str[i + 1] == '>')
			ft_error(&(*data), "one_outred");
		if (data->error != NULL)
			return ;
		i++;
	}
}

void	check_outredirect(t_data *data)
{
	t_pipes	*p;
	int		i;

	p = data->pipes;
	while (p != NULL)
	{
		i = 0;
		check_outredirect1(&(*data), p, p->cmd, i);
		if (data->error != NULL)
			return ;
		else
			check_outredirect2(&(*data), p, p->cmd, i);
		if (data->error != NULL)
			return ;
		p = p->next;
	}
}
