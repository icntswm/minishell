/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:30:36 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/25 18:30:37 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_pipes_dupping(t_data *data)
{
	int	in_id;
	int	out_id;

	in_id = get_in_fd(data, 0);
	out_id = get_out_fd(data, 0);
	if (in_id != 0)
		dup2(in_id, 0);
	if (out_id != 0)
		dup2(out_id, 1);
	if (in_id)
		close(in_id);
	if (out_id)
		close(out_id);
	return (0);
}

int	built_in_dupping(t_data *data)
{
	int	in_id;
	int	out_id;

	in_id = get_in_fd(data, 0);
	out_id = get_out_fd(data, 0);
	if (in_id != 0)
		dup2(in_id, 0);
	if (out_id != 0)
		dup2(out_id, 1);
	if (in_id)
		close(in_id);
	if (out_id)
		close(out_id);
	return (0);
}

int	exit_dupping(t_data *data)
{
	int	in_id;
	int	out_id;

	in_id = get_in_fd(data, 0);
	out_id = get_out_fd(data, 0);
	if (in_id)
		close(in_id);
	if (out_id)
		close(out_id);
	return (0);
}
