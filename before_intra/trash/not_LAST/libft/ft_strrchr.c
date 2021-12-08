/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:40 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 17:48:35 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)a)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
