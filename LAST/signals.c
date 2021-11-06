#include "minishell.h"

void	ctrl_c(int status)
{
	write(1, "\b\b  \n", 5);
	make_heredoc_question_error(130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int status)
{
	printf("\b\b  \b\b");
}

void	make_heredoc_question_error(int num)
{
	int		file;
	char	*str;

	str = NULL;
	file = open("quest_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	str = ft_itoa(num);
	write(file, str, ft_strlen(str));
	close(file);
	free(str);
}

void	ctrl_c_redirect_heredoc(int status)
{
	int		file;
	char	*str;

	str = NULL;
	write(1, "\n", 1);
	file = open("heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, "ctrl_c_redirect_heredoc",
		ft_strlen("ctrl_c_redirect_heredoc"));
	close(file);
	make_heredoc_question_error(130);
	rl_on_new_line();
	exit(1);
}

void	ctrl_c_pipe_heredoc(int status)
{
	write(1, "\b\b  \n", 5);
	make_heredoc_question_error(130);
	rl_on_new_line();
	exit(1);
}

void	ctrl_c_fork(int signal)
{
	write(1, "\b\b  \b\b\n", 7);
	make_heredoc_question_error(130);
}
