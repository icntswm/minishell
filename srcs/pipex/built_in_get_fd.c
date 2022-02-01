#include "minishell.h"

static int	built_in_get_position_info(t_files *outfile)
{
	t_files	*temp;
	int		last_file_pos;
	int		i;

	temp = outfile;
	last_file_pos = 0;
	i = 0;
	while (temp)
	{
		temp->pos = i;
		if (temp->mode != BOTH_MOD)
			last_file_pos = i;
		i++;
		temp = temp->next;
	}
	return (last_file_pos);
}

static int	built_in_open_outfile(char *filename, int mode)
{
	int	fd;

	if (mode == AND_MODE || mode == BOTH_MOD)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	return (fd);
}

int	built_in_get_out_fd(t_data *data, int i, int fd, int final_fd)
{
	int		last_file_pos;
	t_pipes	*p_temp;
	t_files	*f_temp;

	p_temp = data->pipes;
	while (i--)
		p_temp = p_temp->next;
	f_temp = p_temp->outfile;
	last_file_pos = built_in_get_position_info(f_temp);
	while (f_temp)
	{
		if (fd && fd != final_fd)
			close(fd);
		fd = built_in_open_outfile(f_temp->filename, f_temp->mode);
		if (fd == -1)
			return (-1);
		if (f_temp->pos == last_file_pos)
			final_fd = fd;
		f_temp = f_temp->next;
	}
	if (fd && fd != final_fd)
		close(fd);
	return (final_fd);
}

static int	built_in_open_infile(char *filename, int mode, int i)
{
	int		fd;
	char	*name;

	if (mode == AND_MODE)
	{
		name = make_filename(i);
		fd = open(name, O_RDONLY);
		free(name);
	}
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(filename);
		return (-1);
	}
	return (fd);
}

int	built_in_get_in_fd(t_data *data, int i)
{
	int		fd;
	t_pipes	*p_temp;
	t_files	*f_temp;
	int		j;

	fd = 0;
	p_temp = data->pipes;
	j = i;
	while (j--)
		p_temp = p_temp->next;
	f_temp = p_temp->infile;
	while (f_temp)
	{
		if (fd)
			close(fd);
		fd = built_in_open_infile(f_temp->filename, f_temp->mode, i);
		if (fd == -1)
			return (-1);
		f_temp = f_temp->next;
	}
	return (fd);
}
