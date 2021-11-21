/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirect2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:59 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/18 16:36:01 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	check_heredoc_eof(char *name)
{
	char	*str;
	int		file;

	file = open(name, O_RDONLY, 0644);
	get_next_line(file, &str);
	if (str[0] == EOF)
	{
		close(file);
		free(str);
		return (1);
	}
	free(str);
	close(file);
	return (0);
}

int	counter_double_redrct(t_files *infile)
{
	t_files	*f;
	int		counter;

	counter = 0;
	f = infile;
	while (f != NULL)
	{
		if (f->mode == 2)
			counter++;
		f = f->next;
	}
	return (counter);
}

void	error_heredoc_redrct_ctrl_d(char *name, int col)
{
	char	*save1;
	char	*save2;
	char	*save_col;
	int		file;

	save1 = NULL;
	save2 = NULL;
	if (name != NULL)
		save1 = ft_strjoin("warning: here-document \
delimited by end-of-file (wanted '", name);
	else
		save1 = ft_strdup("warning: here-document \
delimited by end-of-file (wanted '");
	save2 = ft_strjoin(save1, "')");
	file = open(".heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, save2, ft_strlen(save2));
	close(file);
	file = open(".heredoc_col", O_CREAT | O_TRUNC | O_RDWR, 0644);
	save_col = ft_itoa(col - 1);
	write(file, save_col, 1);
	close(file);
	printf("minishell: %s\n", save2);
	free(save_col);
	free(save1);
	free(save2);
}

int	check_str(int file, char *str, char *fname, int col)
{
	char	*save_col;

	if (!str)
	{
		error_heredoc_redrct_ctrl_d(fname, col);
		return (-1);
	}
	if ((fname == NULL && str[0] == '\0') || (fname != NULL && ft_strncmp(\
fname, str, ft_strlen(str)) == 0 && ft_strlen(str) > 0
			&& ft_strlen(str) == ft_strlen(fname)))
	{
		col--;
		file = open(".heredoc_col", O_CREAT | O_TRUNC | O_RDWR, 0644);
		save_col = ft_itoa(col);
		write(file, save_col, 1);
		free(save_col);
		free(str);
		return (-1);
	}
	return (0);
}

int	utils_for_read_here(int col, int num_cmd, char *filename)
{
	char	*name;
	char	*itoa;

	name = NULL;
	itoa = NULL;
	if (col == 1)
	{
		itoa = ft_itoa(num_cmd);
		name = ft_strjoin(".heredoc", itoa);
		free(itoa);
	}
	col = help_red_file(col, name, filename);
	if (name)
		free(name);
	return (col);
}
