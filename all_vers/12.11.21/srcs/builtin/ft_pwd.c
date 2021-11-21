/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:57 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:18:58 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **cmd)
{
	char	*buf;

	buf = NULL;
	if (cmd[1] != 0 && cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: shell does not supp\
ort options for pwd.\n", 2);
		return (228);
	}
	buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		perror("minishell");
		return (errno);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
	return (0);
}
