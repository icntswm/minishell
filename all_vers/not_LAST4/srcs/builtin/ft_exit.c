/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:23 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:22:06 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_al_num(char *str)
{
	size_t	res;
	int		sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		res = (res * 10) + *str - '0';
		if (res > 2147483648 || (sign == 1 && res > 2147483647))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **cmd)
{
	if (!cmd[1])
		exit(g_question);
	if (is_al_num(cmd[1]))
	{
		if (cmd[2] == NULL)
			exit(ft_atoi(cmd[1]) % 256);
		ft_putstr_fd("Too many arguments for exit.\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("Not numeric argument.\n", 2);
		exit(255);//check in linux!!!!!!!!!
	}
	return (0);
}
