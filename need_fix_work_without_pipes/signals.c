#include "minishell.h"

void	ctrl_c(int status)
{
	write(1, "\b\b  \n", 5);
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

	write(1, "\n", 1);
	file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, "ctrl_c_redirect_heredoc",
		ft_strlen("ctrl_c_redirect_heredoc"));
	close(file);
	rl_on_new_line();
	// rl_redisplay();
	exit(1);
}

void	ctrl_c_pipe_heredoc(int status)
{
	write(1, "\b\b  \n", 5);
	rl_on_new_line();
	// rl_redisplay();
	exit(1);
}

void	ctrl_c_fork(int signal)
{
	write(1, "\b\b  \b\b\n", 7);
}