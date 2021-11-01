/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:28:05 by squickfi          #+#    #+#             */
/*   Updated: 2021/10/23 18:39:00 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**fill_args2(char *s, char **strs, t_parser_info info)
{
	while (s[info.end])
	{
		info.start = info.end;
		if (s[info.end] == '\"' || s[info.end] == '\'')
		{
			info.quote = quote_case(s + info.end, s[info.end]);
			if (info.quote == -1)
				return (free_args_and_return_null(info.temp, strs));
			info.start++, info.end += info.quote - 1;
		}
		else
			while (s[info.end] && s[info.end] != ' ')
				info.end++;
		strs[info.temp] = ft_substr(s, info.start, info.end - info.start);
		if (!strs[info.temp])
			return (free_args_and_return_null(info.temp, strs));
		info.temp++;
		if (info.quote && (s[info.end] == '\"' || s[info.end] == '\''))
			info.end++;
		while (s[info.end] == ' ')
			info.end++;
		info.quote = 0;
	}
	return (strs);
}

static char	**fill_args(char *s, char **strs)
{
	t_parser_info	info;

	info.end = 0;
	info.start = 0;
	info.quote = 0;
	info.temp = 0;
	while (s[info.end] && s[info.end] == ' ')
		info.end++;
	fill_args2(s, strs, info);
	strs[count_words(s, info)] = NULL;
	return (strs);
}

char	**split_args(char *s)
{
	char			**strs;
	t_parser_info	info;
	int				words;

	info.end = 0;
	info.start = 0;
	info.quote = 0;
	info.temp = 0;
	words = count_words(s, info);
	if (words == -1)
		return (NULL);
	if (!s)
		return (NULL);
	strs = malloc((words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (!fill_args(s, strs))
		return (NULL);
	return (strs);
}
