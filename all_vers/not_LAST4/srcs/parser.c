/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:42:21 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/09 00:25:38 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser4(t_data *data)
{
	if (ft_strncmp(data->error, "warning: here-document delimited", \
		ft_strlen("warning: here-document delimited")) == 0)
	{
		free(data->error);
		data->error = NULL;
	}
	else if ((ft_strncmp(data->error, "warning: here-document delimited", \
			ft_strlen("warning: here-document delimited")) != 0)
		&& (ft_strncmp(data->error, "ctrl_c_redirect_heredoc", \
				ft_strlen("ctrl_c_redirect_heredoc")) != 0)
		&& data->error[0] != '\0')
	{
		if (data->error[0] != '\0')
			printf("minishell: %s\n", data->error);
	}
}

void	parser3(t_data *data)
{
	cutting_file(&(*data));
	cutting_redirect(&(*data));
	remove_spaces_cmd(&(*data));
	remove_spaces_file(&(*data));
	make_cmd_argv(&(*data));
	quotes_and_dollar(&(*data));
	make_heredoc_files(&(*data));
	signal(SIGINT, ctrl_c);
	check_heredoc_file(&(*data));
	// list_cmd_print(data->pipes);
	if (data->error != NULL)
		parser4(&(*data));
}

void	parser2(t_data *data)
{
	search_redirect_position(&(*data), '<');
	search_redirect_position(&(*data), '>');
	if (data->error == NULL)
	{
		make_list(&(*data), '<');
		make_list(&(*data), '>');
	}
}

void	parser1(t_data *data)
{
	cut_pipe(&(*data));
	remove_spaces_pipe(&(*data));
	if (data->error == NULL)
		check_outredirect(&(*data));
	if (data->error == NULL)
		check_inredirect(&(*data));
	if (data->error == NULL)
	{
		heredoc_pipe(&(*data));
		check_heredoc_file(&(*data));
		if (data->error == NULL)
			check_outredirect(&(*data));
		if (data->error == NULL)
			check_inredirect(&(*data));
	}
}

void	parser(t_data *data)
{
	data->col_pipes = 0;
	data->error = NULL;
	data->pos_pipe = NULL;
	data->pipes = NULL;
	remove_spaces_in_line(&(*data));
	search_pipe_position(&(*data));
	check_space_numfile(&(*data));
	if (data->error == NULL)
	{
		parser1(&(*data));
		if (data->error == NULL)
			parser2(&(*data));
	}
	if (data->error)
	{
		if ((ft_strncmp(data->error, "ctrl_c_pipe_heredoc", \
			ft_strlen("ctrl_c_pipe_heredoc"))) != 0
			&& (ft_strncmp(data->error, "ctrl_c_redirect_heredoc", \
				ft_strlen("ctrl_c_redirect_heredoc"))) != 0)
			printf("minishell: %s\n", data->error);
	}
	else
		parser3(&(*data));
}
