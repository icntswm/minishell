/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:31:06 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:31:08 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memcpy(void *a, const void *b, size_t lenght)
{
	if (!a && !b)
		return (0);
	while (lenght > 0)
	{
		lenght--;
		((char *)a)[lenght] = ((char *)b)[lenght];
	}
	return (a);
}
