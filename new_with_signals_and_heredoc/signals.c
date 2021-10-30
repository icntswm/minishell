#include "minishell.h"

void	ctrl_c(int status)
{
	printf("\b\b  \n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int status)
{
	printf("\b\b  \b\b");
}

void	ctrl_c_redirect_heredoc(int status)
{
	int	file;

	file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, "ctrl_c_redirect_heredoc",
		ft_strlen("ctrl_c_redirect_heredoc"));
	close(file);
	printf("\b\b  \n");
	rl_redisplay();
	exit(0);
}

void	ctrl_c_pipe_heredoc(int status)
{
	printf("\b\b  \n");
	rl_redisplay();
	exit(0);
}
