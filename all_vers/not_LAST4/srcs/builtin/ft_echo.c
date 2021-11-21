/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:19 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:18:20 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_echo(char **cmd)
{
	if (*cmd && ft_strncmp(*cmd, "-n", 3) == 0)
	{
		cmd++;
		while (*cmd)
		{
			ft_putstr_fd(*cmd, 1);
			cmd++;
			if (*cmd != NULL)
				ft_putchar_fd(' ', 1);
		}
		return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	cmd++;
	if (*cmd && **cmd == '-' && *(*cmd + 1) != 'n')
	{
		ft_putstr_fd("minishell: shell supp\
orts only -n option for echo.\n", 2);
		return (228);
	}
	if (help_echo(cmd) == 0)
		return (0);
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		ft_putchar_fd(' ', 1);
		cmd++;
	}
	ft_putchar_fd('\n', 1);
	return (0);
}
