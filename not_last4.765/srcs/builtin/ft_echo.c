/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:19 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/27 17:35:13 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_n(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] != '-')
		return (0);
	i++;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	help_echo(char **cmd)
{
	if (*cmd && is_all_n(*cmd))
	{
		cmd++;
		while (*cmd && is_all_n(*cmd))
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
orts only -n option for echo\n", 2);
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
