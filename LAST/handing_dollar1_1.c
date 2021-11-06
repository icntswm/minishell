/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handing_dollar1_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:36 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:37 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*help_dollar_quest(int question)
{
	int		file;
	char	*save1;

	save1 = NULL;
	if (access("quest_error", F_OK) == 0)
	{
		file = open("quest_error", O_RDONLY, 0644);
		get_next_line(file, &save1);
		close(file);
	}
	else
	{
		file = open("quest_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
		close(file);
		save1 = ft_itoa(question);
	}
	return (save1);
}

int	dollar_question(int i, char *str, char **new)
{
	char	*save1;
	char	*save2;
	char	*save3;
	int		start;

	save1 = help_dollar_quest(question);
	question = 127;
	start = ++i;
	while (str[i] && str[i] != '$')
		i++;
	save2 = ft_substr(str, start, i - start);
	save3 = *new;
	*new = ft_strjoin(save3, save1);
	free(save3);
	save3 = *new;
	*new = ft_strjoin(save3, save2);
	free(save3);
	free(save1);
	free(save2);
	if (str[i] == '$')
		i--;
	return (i);
}

int	dollar_pid(t_data *data, int i, char *str, char **new)
{
	char	*save1;
	char	*save2;
	char	*save3;
	int		start;
	int		file;

	start = ++i;
	save1 = ft_itoa(data->get_pid);
	while (str[i] && str[i] != '$')
		i++;
	save2 = ft_substr(str, start, i - start);
	save3 = *new;
	*new = ft_strjoin(save3, save1);
	free(save3);
	save3 = *new;
	*new = ft_strjoin(save3, save2);
	free(save3);
	free(save1);
	free(save2);
	if (str[i] == '$')
		i--;
	return (i);
}
