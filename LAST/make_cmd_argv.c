#	include "minishell.h"

int	check_size_argv(char *str)
{
	int	i;
	int	col_argv;

	i = 0;
	col_argv = 0;
	while (str[i])
	{
		if (str[i] == 34)
			i = skip_quotes(str, 34, i);
		else if (str[i] == 39)
			i = skip_quotes(str, 39, i);
		if (str[i] == ' ')
		{
			col_argv++;
			while (str[i] && str[i] == ' ')
				i++;
			i--;
		}
		i++;
	}
	return (col_argv);
}

int	help_fill_argv(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34)
			i = skip_quotes(str, 34, i);
		else if (str[i] == 39)
			i = skip_quotes(str, 39, i);
		if (str[i] == ' ' || str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	fill_cmd_argv(char *str, char ***cmd_argv)
{
	int		i;
	int		j;
	int		start;
	int		size;
	char	**array;

	i = 0;
	j = 0;
	start = 0;
	size = check_size_argv(str);
	array = (char **)malloc(sizeof(char *) * (size + 2));
	while (j < size + 1)
	{
		i = help_fill_argv(str, i);
		array[j] = ft_substr(str, start, i - start);
		j++;
		while (str[i] && str[i] == ' ')
			i++;
		start = i;
	}
	array[j] = '\0';
	*cmd_argv = array;
	return (size + 1);
}

void	make_cmd_argv(t_data *data)
{
	t_pipes	*p;

	p = data->pipes;
	while (p != NULL)
	{
		p->size_cmd_argv = fill_cmd_argv(p->cmd, &p->cmd_argv);
		p = p->next;
	}
}
