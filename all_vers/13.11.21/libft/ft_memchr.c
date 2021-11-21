/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:30:24 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:30:25 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memchr(void *a, int c, size_t lenght)
{
	size_t	i;

	i = 0;
	while (i < lenght)
	{
		if (((unsigned char *)a)[i] == (unsigned char)c)
		{
			return ((unsigned char *)a + i);
		}
		i++;
	}
	return (NULL);
}
