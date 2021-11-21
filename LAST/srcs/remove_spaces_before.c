/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:34 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:25:35 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	remove_spaces_in_line(t_data *data)
{
	char	*save;

	save = data->line;
	data->line = ft_chartrim(save, ' ');
	free(save);
}

char	*ft_chartrim(char *s1, char set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	end = ft_strlen(s1);
	start = 0;
	i = 0;
	while (s1[start] && s1[start] == set)
		start++;
	while (end > start && s1[end - 1] == set)
		end--;
	str = (char *)malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
