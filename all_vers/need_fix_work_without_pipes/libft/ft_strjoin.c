/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:34:24 by fkenned           #+#    #+#             */
/*   Updated: 2021/04/26 17:34:25 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	// if (s1 == NULL || s2 == NULL)
	// 	return (NULL);
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (s1 != NULL)
		str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	else
		str = (char *)malloc(sizeof(char) * (len_s2 + 1));
	if (s1 != NULL)
	{
		while (s1[i])
			str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}