#include "../minishell.h"

static int	make_here_doc_files(t_data *data, int i)
{
	t_pipes	*p;
	t_files	*f;
	char	*name;
	int		ret;

	p = data->pipes;
	while (p)
	{
		f = p->infile;
		while (f)
		{
			if (f->mode == AND_MODE)
			{
				name = make_filename(i);
				ret = make_here_doc_file(f->filename, name);
				if (ret)
					return (ret);
				free(name);
			}
			f = f->next;
		}
		p = p->next, i++;
	}
	return (0);
}

int	unlink_here_doc_files(t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	while (i <= data->col_pipes)
	{
		name = make_filename(i);
		if (access(name, F_OK) == 0)
		{
			if (unlink(name) == -1)
			{
				perror("Unlink error");
				free(name);
				return (1);
			}
		}
		free(name);
		i++;
	}
	return (0);
}

int	pipex(t_data *data, char ***envp)
{
	int		**fd;
	pid_t	*pid;
	int		i;
	int 	status;
	char	*name;

	if (data->col_pipes == 0)
		return (work_without_pipes(data, envp));
	fd = make_fds(data->col_pipes);
	pid = malloc((data->col_pipes + 1) * sizeof(pid_t *));
	if (!pid)
		exit(EXIT_FAILURE);
	handle_multipipes(data, envp, fd, pid);
	close_fds(data->col_pipes, fd);
	i = 0;
	while (i < data->col_pipes + 1)
		waitpid(pid[i++], &status, 0);
	unlink_here_doc_files(data);
	free_fds(data->col_pipes, fd), free(pid);
	return (status);
}
