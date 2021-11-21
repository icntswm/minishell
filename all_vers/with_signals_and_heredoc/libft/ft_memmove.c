/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:31:28 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:31:29 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memmove(void *a, const void *b, size_t lenght)
{
	int	i;

	if (!a && !b)
		return (NULL);
	if (a > b)
	{
		i = lenght - 1;
		while (i >= 0)
		{
			((char *)a)[i] = ((char *)b)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)lenght)
		{
			((char *)a)[i] = ((char *)b)[i];
			i++;
		}
	}
	return (a);
}
