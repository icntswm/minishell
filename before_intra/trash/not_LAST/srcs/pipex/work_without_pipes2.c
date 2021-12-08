#include "minishell.h"

void	check_status_without_pipe(int status, char **cmd)
{
	int		file;
	char	*str;

	file = open("quest_error", O_RDONLY, 0644);
	if (file != -1)
	{
		get_next_line(file, &str);
		close(file);
		if (status == 512 && cmd != NULL && ft_atoi(str) != 1
			&& ft_atoi(str) != -111)
			make_heredoc_question_error(2);
		else if (status == 256 && cmd != NULL)
			make_heredoc_question_error(1);
		else if (ft_atoi(str) == -111)
			make_heredoc_question_error(1);
		free(str);
	}
}

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

void	help_get_path(t_data *data, int num, char **cmd_args)
{
	if (num == data->col_pipes)
		make_heredoc_question_error(127);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	write(2, ": command not found\n", 20);
}
