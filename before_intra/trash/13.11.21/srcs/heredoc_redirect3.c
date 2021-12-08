#include "minishell.h"

int		check_str_eof1(int status, char *str, char *fname, int col)
{
	if (str[0] == '\0' && status == 0)
	{
		error_heredoc_redrct_ctrl_d(fname, col);
		return (-1);
	}
	return (0);
}

int		check_str_eof2(int file, char *str, char *fname, int col)
{
	char *save_col;

	save_col = NULL;
	if ((fname == NULL && str[0] == '\0') || (fname != NULL && ft_strncmp(\
fname, str, ft_strlen(str)) == 0 && ft_strlen(str) > 0
			&& ft_strlen(str) == ft_strlen(fname)))
	{
		col--;
		file = open("heredoc_col", O_CREAT | O_TRUNC | O_RDWR, 0644);
		save_col = ft_itoa(col);
		write(file, save_col, 1);
		free(save_col);
		free(str);
		return (-1);
	}
	return (0);
}