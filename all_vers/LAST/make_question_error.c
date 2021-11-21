/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_question_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:44:51 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/07 16:44:52 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
