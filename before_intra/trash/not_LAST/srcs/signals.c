/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:44 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/07 16:43:43 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int status)
{
	status = 1;
	write(1, "\b\b  \n", 5);
	make_heredoc_question_error(130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int status)
{
	status = 1;
	printf("\b\b  \b\b");
}

void	ctrl_c_redirect_heredoc(int status)
{
	int		file;

	status = 1;
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
	status = 1;
	write(1, "\b\b  \n", 5);
	make_heredoc_question_error(130);
	rl_on_new_line();
	exit(1);
}

void	ctrl_c_fork(int status)
{
	status = 1;
	write(1, "\b\b  \b\b\n", 7);
	make_heredoc_question_error(130);
}
