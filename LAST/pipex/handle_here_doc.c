/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:27:52 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/05 01:50:27 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
		i++;
	}
	return (0);
}

char	*make_filename(int i)
{
	char	*num;
	char	*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("heredoc", num);
	free(num);
	return (filename);
}

static int	make_here_doc_cycle(char *line, char *name, char *limiter, int fd)
{
	if (get_next_line(0, &line) == -1)
	{
		free(name);
		return (1);
	}
	while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &line) == -1)
		{
			free(name);
			return (1);
		}
	}
	return (0);
}

int	make_here_doc_file(char	*limiter, char *name)
{
	int		fd;
	char	*line;

	fd = open(name, O_RDWR | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
	{
		perror("Error");
		return (1);
	}
	write(1, "heredoc> ", 9);
	if (make_here_doc_cycle(line, name, limiter, fd))
		return (1);
	close(fd);
	return (0);
}
