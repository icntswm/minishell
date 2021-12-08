/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:30:04 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:30:05 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memccpy(void *a, const void *b, int c, size_t lenght)
{
	size_t	i;

	i = 0;
	while (i < lenght)
	{
		((unsigned char *)a)[i] = ((unsigned char *)b)[i];
		if (((unsigned char *)b)[i] == (unsigned char)c)
			return ((unsigned char *)a + i + 1);
		i++;
	}
	return (NULL);
}
