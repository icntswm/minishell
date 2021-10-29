/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 11:13:25 by fkenned           #+#    #+#             */
/*   Updated: 2021/05/10 11:13:27 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "get_next_line.h"

static char	*save_buf(char *buffer)
{
	char	*n_buf;
	char	*start_adr_tmp;

	n_buf = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (n_buf == NULL)
		return (NULL);
	start_adr_tmp = n_buf;
	while (*buffer)
		*n_buf++ = *buffer++;
	*n_buf = '\0';
	return (start_adr_tmp);
}

static int	ft_check_mzero_readb(char **line, char **box)
{
	int		i;
	char	*save;

	i = 0;
	while ((*box)[i] != '\n' && (*box)[i] != '\0')
		i++;
	if ((*box)[i] == '\n')
	{
		*line = ft_substr(*box, 0, i);
		save = save_buf(&(*box)[i + 1]);
		free(*box);
		*box = save;
	}
	else
	{
		if (*box != NULL)
		{
			*line = save_buf(*box);
			free(*box);
			*box = NULL;
		}
		return (0);
	}
	return (1);
}

static int	ft_check_neg_zero_readb(char **line, char **box, int read_b)
{
	int	i;

	i = 0;
	if (read_b < 0)
		return (-1);
	else if (read_b == 0 && *box == NULL)
	{
		*line = ft_calloc(1, 1);
		return (0);
	}
	else
		return (ft_check_mzero_readb(line, &(*box)));
}

static void	ft_savejoin(char **box, char *buffer)
{
	char	*save;

	save = ft_strjoin(*box, buffer);
	free(*box);
	*box = save;
}

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	int			read_b;
	static char	*box;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	read_b = 6;
	while (read_b > 0)
	{	
		read_b = read(fd, buffer, BUFFER_SIZE);
		if (read_b > 0)
			buffer[read_b] = '\0';
		else
			break ;
		if (box != NULL)
			ft_savejoin(&box, buffer);
		else
			box = save_buf(buffer);
		if (ft_strchr(box, '\n') != NULL)
			break ;
	}
	return (ft_check_neg_zero_readb(line, &box, read_b));
}
