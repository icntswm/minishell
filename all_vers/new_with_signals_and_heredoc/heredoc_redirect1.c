#	include "minishell.h"

int	help_red_file(int col, char *name, char *fname)
{
	char	*str;
	int		file;

	while (1)
	{
		if (col == 1)
			file = open(name, O_CREAT | O_APPEND | O_RDWR, 0644);
		str = readline("> ");
		if (!str && col == 1)
		{
			close(file);
			file = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
		}
		if ((check_str(file, str, fname, col)) == -1)
			break ;
		if (col == 1 && ft_strlen(str) > 0)
		{
			write(file, str, ft_strlen(str));
			write(file, "\n", 1);
		}
		free(str);
	}
	return (col);
}

int	read_heredoc_col(int col)
{
	char	*new_col;
	int		file;

	file = open("heredoc_col", O_RDONLY, 0644);
	if (file != -1)
	{
		get_next_line(file, &new_col);
		close(file);
		unlink("heredoc_col");
		col = ft_atoi(new_col);
		free(new_col);
	}
	return (col);
}

int	make_read_here_file2(int num_cmd, int col, char *filename)
{
	pid_t	pid1;
	char	*name;
	char	*itoa;

	pid1 = fork();
	if (pid1 == 0)
	{
		if (col == 1)
		{
			itoa = ft_itoa(num_cmd);
			name = ft_strjoin("heredoc", itoa);
			free(itoa);
		}
		col = help_red_file(col, name, filename);
		if (col == 0)
			free(name);
		exit(0);
	}
	else
	{
		waitpid(pid1, 0, 0);
		col = read_heredoc_col(col);
	}
	return (col);
}

void	make_red_here_file(t_files *infile, int num_cmd)
{
	t_files	*f;
	pid_t	pid1;
	int		col;

	f = infile;
	col = counter_double_redrct(f);
	while (f != NULL)
	{
		if (f->mode == 2)
			col = make_read_here_file2(num_cmd, col, f->filename);
		f = f->next;
	}
}

void	make_heredoc_files(t_data *data)
{
	t_pipes	*p;
	pid_t	pid;
	pid_t	pid1;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	p = data->pipes;
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_redirect_heredoc);
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
