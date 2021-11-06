/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:39 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:40 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_and_end_line(char *str, char *new, int i)
{
	char	*save1;
	char	*save_new;

	save1 = NULL;
	save_new = NULL;
	if (new == NULL)
	{
		save1 = ft_substr(str, 0, i + 1);
		save_new = new;
		new = ft_strjoin(save_new, save1);
		free(save_new);
		free(save1);
	}
	else
	{
		save_new = new;
		new = ft_strjoin(save_new, "$");
		free(save_new);
	}
	return (new);
}

int	help_dollar_change(char *str, char **new, int i, char *dollar)
{
	int		start;
	char	*save2;
	char	*save_new;

	start = i;
	save2 = NULL;
	save_new = NULL;
	while (str[i] && str[i] != '$')
		i++;
	if (i != start)
		save2 = ft_substr(str, start, i - start);
	save_new = *new;
	*new = ft_strjoin(save_new, dollar);
	free(dollar);
	free(save_new);
	if (i != start)
	{
		save_new = *new;
		*new = ft_strjoin(save_new, save2);
		free(save_new);
		free(save2);
	}
	if (str[i] == '$')
		i--;
	return (i);
}

int	dollar_change(char *str, char **new, int i, t_data *data)
{
	int		start;
	char	*dollar;

	start = i;
	dollar = NULL;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != 39)
	{
		i++;
		if ((str[i] > 47 && str[i] < 58) || (str[i] > 64 && str[i] < 91)
			|| str[i] == 95 || (str[i] > 96 && str[i] < 123))
		{
		}
		else
			break ;
	}
	dollar = ft_substr(str, start, i - start);
	dollar = search_envp_dollar(&(*data), dollar);
	i = help_dollar_change(str, &(*new), i, dollar);
	return (i);
}

char	*help_check_dollar(char *str, char *new)
{
	int		i;
	char	*save_new;

	i = 0;
	save_new = NULL;
	if (new != NULL)
	{
		free(str);
		return (new);
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] == '\0')
			{
				save_new = str;
				str = ft_substr(save_new, 0, i);
				free(save_new);
				break ;
			}
			i++;
		}
	}
	return (str);
}

char	*check_dollar(t_data *data, char *str, int lenght_str, int cmd_len)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$' && str[i + 1] == '?')
			i = dollar_question(++i, str, &new);
		else if (str[i] == '$' && str[i + 1] == '$')
			i = dollar_pid(&(*data), ++i, str, &new);
		else if (str[i] == '$' && str[i + 1] != '\0')
		{
			i++;
			if (new == NULL)
				new = dollar_and_new_is_null(str, new, i);
			i = dollar_change(str, &new, i, &(*data));
		}
		else if (str[i] == '$' && str[i + 1] == '\0'
			&& cmd_len + i == lenght_str - 1)
			new = dollar_and_end_line(str, new, i);
		i++;
	}
	str = help_check_dollar(str, new);
	return (str);
}
