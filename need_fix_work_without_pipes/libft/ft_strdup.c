/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:34:11 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:34:12 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	lenght;
	char	*cop;

	i = 0;
	lenght = ft_strlen(str);
	cop = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!cop)
		return (NULL);
	while (str[i])
	{
		cop[i] = str[i];
		i++;
	}
	cop[i] = '\0';
	return (cop);
}
