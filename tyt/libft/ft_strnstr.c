/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:36:32 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:36:33 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t lenght)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*(char *)little == '\0')
		return ((char *)big);
	while (i < lenght && big[i])
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (i + j < lenght && big[i + j] == little[j]
				&& big[i + j] && little[j])
				j++;
			if (!little[j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
