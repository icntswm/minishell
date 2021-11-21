/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:27:39 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 17:53:08 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static char	*ft_itoa_swap(char *s)
{
	int		i;
	int		j;
	char	a;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		a = s[i];
		s[i] = s[j];
		s[j] = a;
		i++;
		j--;
	}
	return (s);
}

static int	ft_itoa_len(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	ft_itoa_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;
	int		i;

	if (n == (-2147483647 - 1))
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = ft_itoa_sign(n);
	if (sign == 1)
		n = -n;
	str = malloc(sizeof(char) * (ft_itoa_len(n) + sign + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (n != 0)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign != 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_itoa_swap(str));
}
