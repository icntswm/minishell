#	include "minishell.h"

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

void	error_heredoc_redrct_ctrl_d(char *name)
{
	char	*save1;
	char	*save2;
	int		file;

	save1 = NULL;
	save2 = NULL;
	save1 = ft_strjoin(
			"warning: here-document delimited by end-of-file (wanted '", name);
	save2 = ft_strjoin(save1, "')");
	file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, save2, ft_strlen(save2));
	close(file);
	free(save1);
	free(save2);
	exit (0);
}

int	help_red_file(int file, int col, char *name, char *fname)
{
	char	*str;

	while (1)
	{
		if (col == 1)
			file = open(name, O_CREAT | O_APPEND | O_RDWR, 0644);
		str = readline("> ");
		if (!str)
			error_heredoc_redrct_ctrl_d(fname);
		if (ft_strncmp(fname, str, ft_strlen(str)) == 0 && ft_strlen(str) > 0)
		{
			col--;
			free(str);
			break ;
		}
		if (col == 1 && ft_strlen(str) > 0)
		{
			write(file, str, ft_strlen(str));
			write(file, "\n", 1);
		}
		free(str);
	}
	if (col == 0)
		close(file);
	return (col);
}

void	make_red_here_file(t_files *infile, int num_cmd)
{
	t_files	*f;
	int		col;
	int		file;
	char	*name;
	char	*itoa;

	itoa = NULL;
	f = infile;
	col = counter_double_redrct(f);
	while (f != NULL)
	{
		if (f->mode == 2)
		{
			if (col == 1)
			{
				itoa = ft_itoa(num_cmd);
				name = ft_strjoin("heredoc", itoa);
				free(itoa);
			}
			col = help_red_file(file, col, name, f->filename);
			if (col == 0)
				free(name);
		}
		f = f->next;
	}
}

void	make_heredoc_files(t_data *data)
{
	t_pipes	*p;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	p = data->pipes;
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_heredoc);
		while (p != NULL)
		{
			if (p->infile)
				make_red_here_file(p->infile, p->num);
			p = p->next;
		}
		exit (0);
	}
	else if (pid > 0)
		wait (0);
	if (pid == 0)
		exit (0);
	signal(SIGINT, ctrl_c);
}
