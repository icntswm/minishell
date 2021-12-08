/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:25:44 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/22 00:25:37 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int status)
{
	status++;
	g_question = 130;
	write(1, "\b\b  \n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int status)
{
	status++;
	printf("\b\b  \b\b");
}

void	ctrl_c_redirect_heredoc(int status)
{
	int		file;

	status++;
	write(1, "\n", 1);
	file = open(".heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(file, "ctrl_c_redirect_heredoc",
		ft_strlen("ctrl_c_redirect_heredoc"));
	rl_on_new_line();
	close(file);
	exit(130);
}

void	ctrl_c_pipe_heredoc(int status)
{
	status++;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}

void	ctrl_c_fork(int status)
{
	status++;
	write(1, "\b\b  \b\b\n", 7);
}
