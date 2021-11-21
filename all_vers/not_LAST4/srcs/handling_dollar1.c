/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:39 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/07 18:22:21 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	symbol;

	start = i;
	dollar = NULL;
	symbol = str[i];
	if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] \
			<= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
	{
		while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != 39)
			i++;
		*new = ft_substr(str, start - 1, i - (start - 1));
		if (str[i] == '$')
			i--;
		return (i);
	}
	i = help_dollar_change2(i, symbol, str);
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

int	check_dollar2(t_data *data, int i, char *str, char **new)
{
	if (str[i] == '$' && str[i + 1] == '?')
	{	
		i++;
		if (*new == NULL)
			*new = dollar_and_new_is_null(str, *new, i);
		i = dollar_question(i, str, &(*new));
	}
	else if (str[i] == '$' && str[i + 1] == '$')
	{
		i++;
		if (*new == NULL)
			*new = dollar_and_new_is_null(str, *new, i);
		i = dollar_pid(&(*data), i, str, &(*new));
	}
	else if (str[i] == '$' && str[i + 1] != '\0')
	{
		i++;
		if (*new == NULL)
			*new = dollar_and_new_is_null(str, *new, i);
		i = dollar_change(str, &(*new), i, &(*data));
	}
	return (i);
}

char	*check_dollar(t_data *data, char *str, int lenght_str, int cmd_len)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (i < ft_strlen(str))
	{
		if ((str[i] == '$' && str[i + 1] == '?')
			|| (str[i] == '$' && str[i + 1] == '$')
			|| (str[i] == '$' && str[i + 1] != '\0'))
			i = check_dollar2(&(*data), i, str, &new);
		else if (str[i] == '$' && str[i + 1] == '\0'
			&& cmd_len + i == lenght_str - 1)
			new = dollar_and_end_line(str, new, i);
		i++;
	}
	str = help_check_dollar(str, new);
	return (str);
}
