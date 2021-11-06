/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:24:42 by fkenned           #+#    #+#             */
/*   Updated: 2021/11/06 18:24:43 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	compare_dollar_and_export(char *exp, char *dollar)
{
	int	i;

	i = 0;
	while (exp[i] && exp[i] != '=')
	{
		if (exp[i] != dollar[i])
			return (1);
		i++;
	}
	if (dollar[i] != '\0')
		return (1);
	return (0);
}

char	*search_envp_dollar(t_data *data, char *dollar)
{
	t_envp	*p;
	int		i;

	i = 0;
	p = data->exp;
	while (p != NULL)
	{
		if (compare_dollar_and_export(p->var, dollar) == 0)
		{
			while (p->var[i] && p->var[i] != '=')
				i++;
			free(dollar);
			dollar = ft_substr(p->var, i + 1, ft_strlen(p->var) - (i + 1));
			return (dollar);
		}		
		p = p->next;
	}
	free(dollar);
	return (ft_strdup(""));
}

char	*dollar_and_new_is_null(char *str, char *new, int i)
{
	char	*save1;
	char	*save_new;

	save1 = NULL;
	save_new = NULL;
	save1 = ft_substr(str, 0, i - 1);
	save_new = new;
	new = ft_strjoin(save_new, save1);
	free(save_new);
	free(save1);
	return (new);
}
