/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:24:52 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/23 16:57:28 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_slash_fork(int status)
{
	status++;
	printf("Quit\n");
}

int	check_ctrl_return(int status)
{
	if (status == 3)
		return (131);
	return (130);
}

int	search_slash_n(char *array)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (i < ft_strlen(array))
	{
		if (array[i] == '\n')
			col++;
		i++;
	}
	return (col);
}
