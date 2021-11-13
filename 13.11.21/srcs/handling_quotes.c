/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:45 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/11 00:05:00 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	it_quotes(t_data *data, char **new, char *str, int i)
{
	int		start;
	int		quot;
	char	*save1;
	char	*save2;

	save1 = NULL;
	save2 = NULL;
	start = i - 1;
	if (str[i - 1] == 34)
		quot = 34;
	else if (str[i - 1] == 39)
		quot = 39;
	while (str[i] && str[i] != quot)
		i++;
	if (i - (start + 1) > 0)
	{
		save1 = ft_substr(str, start + 1, i - (start + 1));
		if (quot == 34)
			save1 = check_dollar(&(*data), save1, ft_strlen(save1), start);
		save2 = *new;
		*new = ft_strjoin(save2, save1);
		free(save1);
		free(save2);
	}
	return (i);
}

int	not_quotes(t_data *data, char **new, char *str, int i)
{
	int		start;
	char	*save1;
	char	*save2;

	start = i;
	save1 = NULL;
	save2 = NULL;
	while (str[i] && str[i] != 34 && str[i] != 39)
		i++;
	save1 = ft_substr(str, start, i - start);
	save1 = check_dollar(&(*data), save1, ft_strlen(str), start);
	save2 = *new;
	*new = ft_strjoin(save2, save1);
	free(save1);
	free(save2);
	return (i);
}

char	*help_quot(t_data *data, char *str, char *new, int i)
{
	while (str[i])
	{
		if (str[i] == 34)
			i = it_quotes(&(*data), &new, str, ++i);
		else if (str[i] == 39)
			i = it_quotes(&(*data), &new, str, ++i);
		if (str[i] != 34 && str[i] != 39)
		{
			i = not_quotes(&(*data), &new, str, i);
			i--;
		}
		i++;
	}
	return (new);
}

char	*handling_quotes(t_data *data, char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	if (str[0] == 34 || str[0] == 39)
	{
		if (str[0] == 34)
			i = skip_quotes(str, 34, i);
		else
			i = skip_quotes(str, 39, i);
		if (str[i + 1] == ' ')
		{
			i++;
			new = ft_substr(str, 0, i);
		}
		else
			i = 0;
	}
	new = help_quot(&(*data), str, new, i);
	free(str);
	return (new);
}
