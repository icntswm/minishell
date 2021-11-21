/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:28:08 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/23 18:36:56 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**free_split(int temp, char **strs)
{
	while (temp >= 0)
	{
		free(strs[temp]);
		temp--;
	}
	free(strs);
	return (strs);
}

char	**free_args_and_return_null(int temp, char **strs)
{
	free_split(temp, strs);
	return (NULL);
}

int	quote_case(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	return (i + 1);
}

int	count_words(char *s, t_parser_info info)
{
	info.end = 0;
	info.temp = 0;
	while (s[info.temp] == ' ')
		info.temp++;
	while (s[info.temp])
	{
		if (s[info.temp] == '\'' || s[info.temp] == '\"')
		{
			info.quote = quote_case(s + info.temp, s[info.temp]);
			if (info.quote == -1)
				return (-1);
			info.temp += info.quote;
		}
		else
			while (s[info.temp] && s[info.temp] != ' ')
				info.temp++;
		info.end++;
		while (s[info.temp] == ' ')
			info.temp++;
	}
	return (info.end);
}
