/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:24:52 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/22 00:25:07 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_slash_fork(int status)
{
	status++;
	printf("Quit\n");
}

int	check_ctrl_return(int status)
{
	if (status == 3)
		return (131);
	return (130);
}
