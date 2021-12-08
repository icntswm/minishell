/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_numfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:19 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:20 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

char	*psevdo_atoi(char *str, long long i)
{
	long long	res;
	char		*num;

	res = 0;
	num = NULL;
	while (str[i] >= '0' && str[i] <= '9')
	{	
		res = (res * 10) + str[i] - '0';
		i++;
	}
	if (res > 2147483647)
		return (NULL);
	else
		num = ft_itoa(res);
	return (num);
}

void	error_numfile(t_data *data, int save)
{
	char	*str;

	str = psevdo_atoi(data->line, save);
	if (str != NULL)
	{
		data->error = ft_strjoin("syntax error near unexpected token '", str);
		free(str);
		str = data->error;
		data->error = ft_strjoin(str, "'");
		free(str);
	}
}

int	help_space_numfile(t_data *data, int i)
{
	int		save;

	save = 0;
	while (data->line[i] && data->line[i] == ' ')
		i++;
	if (data->line[i] >= '0' && data->line[i] <= '9')
	{
		save = i;
		while (data->line[i] && data->line[i] >= '0' && data->line[i] <= '9')
			i++;
		if (data->line[i] == '>' || data->line[i] == '<')
			error_numfile(&(*data), save);
	}
	else
		i--;
	return (i);
}

void	check_space_numfile(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(data->line))
	{
		if (data->line[i] == 34)
			i = skip_quotes(data->line, 34, i);
		else if (data->line[i] == 39)
			i = skip_quotes(data->line, 39, i);
		else if (i == 0 && data->line[i] == '>' && data->line[i + 1] != '>')
			i = help_space_numfile(&(*data), ++i);
		else if (i > 0 && data->line[i] == '>' && data->line[i + 1] != '>')
			i = help_space_numfile(&(*data), ++i);
		if (data->error)
			break ;
		i++;
	}
}
