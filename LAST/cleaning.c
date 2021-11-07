/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:50:46 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/07 16:16:27 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exp_env(t_envp *list)
{
	t_envp	*p;
	void	*save;

	p = list;
	while (list != NULL)
	{
		save = list->next;
		free(list->var);
		free(list);
		list = save;
	}
}

void	clean_array(char **array, int size_array)
{
	int	i;

	i = 0;
	while (i < size_array)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	clean_position(t_pos *list)
{
	void	*save;
	t_pos	*pos_red;

	pos_red = list;
	while (pos_red != NULL)
	{
		save = pos_red->next;
		free(pos_red);
		pos_red = save;
	}
}

void	clean_file(t_files *list)
{
	void	*save;
	t_files	*file;

	file = list;
	while (file != NULL)
	{
		save = file->next;
		free(file->filename);
		free(file);
		file = save;
	}
}

void	cleaning_all(t_pipes *list)
{
	t_pipes	*p;
	void	*save;

	p = list;
	while (p != NULL)
	{
		save = p->next;
		if (p->pos_outred)
			clean_position(p->pos_outred);
		if (p->outfile)
			clean_file(p->outfile);
		if (p->pos_inred)
			clean_position(p->pos_inred);
		if (p->infile)
			clean_file(p->infile);
		if (p->cmd_argv)
			clean_array(p->cmd_argv, p->size_cmd_argv);
		free(p->cmd);
		free(p);
		p = save;
	}
}
