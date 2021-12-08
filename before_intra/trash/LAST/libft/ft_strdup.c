/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:34:11 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/23 19:57:36 by squickfi         ###   ########.fr       */
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
		exit(1);
	while (str[i])
	{
		cop[i] = str[i];
		i++;
	}
	cop[i] = '\0';
	return (cop);
}
