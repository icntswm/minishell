/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:30:44 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:30:45 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_memcmp(const void *a, const void *b, size_t lenght)
{
	size_t	i;

	i = 0;
	while (i < lenght)
	{
		if (((unsigned char *)a)[i] != ((unsigned char *)b)[i])
		{
			return (((unsigned char *)a)[i] - ((unsigned char *)b)[i]);
		}
		i++;
	}
	return (0);
}
