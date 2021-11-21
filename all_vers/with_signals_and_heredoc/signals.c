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

void	ctrl_c_heredoc(int status)
{
	printf("\b\b  \n");
	rl_redisplay();
	exit(0);
}
