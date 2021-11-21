/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:56 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:33:57 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strchr(const char *str, int a)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)a)
		i++;
	if (str[i] == (char)a)
	{
		return ((char *)str + i);
	}
	return (NULL);
}
