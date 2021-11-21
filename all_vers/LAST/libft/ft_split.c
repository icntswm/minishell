/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:01:50 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 17:49:56 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int	ft_split_col(char const *s, char c)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			col++;
		}
	}
	return (col);
}

static char	*ft_split_mword(char const *s, char *word, int len_word, int i)
{
	int	j;

	j = 0;
	while (len_word > 0)
	{
		word[j] = s[i - len_word];
		j++;
		len_word--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**ft_split_len_word(char **array, char const *s, char c, int col)
{
	int	i;
	int	len_word;
	int	j;

	j = 0;
	len_word = 0;
	i = 0;
	while (s[i] && j < col)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len_word++;
		}
		array[j] = (char *)malloc(sizeof(char) * (len_word + 1));
		if (!array)
			return (ft_split_free (array));
		ft_split_mword(s, array[j], len_word, i);
		len_word = 0;
		j++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *ss, char c)
{
	int		i;
	int		col;
	char	**array;
	char	*s;

	if (!ss)
		return (NULL);
	i = 0;
	s = (char *)ss;
	s = ft_strtrim(ss, &c);
	if (!s)
		return (NULL);
	col = ft_split_col(s, c);
	array = (char **)malloc(sizeof(char *) * (col + 1));
	if (!array)
		return (NULL);
	ft_split_len_word(array, s, c, col);
	free(s);
	return (array);
}
