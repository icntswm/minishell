/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:39 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/12 00:58:11 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countwords(const char *s, char c)
{
	int	count;
	int	words;

	count = 0;
	words = 0;
	while (s[count] == c && c)
		count++;
	while (s[count])
	{
		while (s[count] && s[count] != c)
			count++;
		words++;
		while (s[count] == c && c)
			count++;
	}
	return (words);
}

static char	**freesplit(int temp, char **strs)
{
	while (temp >= 0)
	{
		free(strs[temp]);
		temp--;
	}
	free(strs);
	return (strs);
}

static char	**fillarr(const char *s, char **strs, char c)
{
	int	count;
	int	temp;
	int	start;

	count = 0;
	temp = 0;
	while (s[count] == c && c)
		count++;
	while (s[count])
	{
		start = count;
		while (s[count] && s[count] != c)
			count++;
		strs[temp] = ft_substr(s, start, count - start);
		if (!strs[temp])
		{
			freesplit(temp, strs);
			return (NULL);
		}
		temp++;
		while (s[count] == c && c)
			count++;
	}
	strs[temp] = NULL;
	return (strs);
}

char	**ftt_split(char const *s, char c)
{
	char	**strs;

	// if (!s)
	// 	exit(EXIT_FAILURE); //вылетает, если сделать unset PATH, export PATH=, ls
	if (!s)
		return(NULL);
	strs = malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!strs)
		exit(EXIT_FAILURE);
	if (!fillarr(s, strs, c))
		exit(EXIT_FAILURE);
	return (strs);
}
