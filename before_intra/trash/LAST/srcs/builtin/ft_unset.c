/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <fkenned@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:59 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/23 14:48:40 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_cycle(t_envp *temp1, t_envp *temp2, char *v, t_envp **list)
{
	if ((ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '=') || \
		(ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '\0'))
	{
		temp2 = temp1->next;
		free(temp1->var);
		free(temp1);
		*list = temp2;
		return ;
	}
	while (temp1->next)
	{
		if ((ft_strncmp(temp1->next->var, v, ft_strlen(v) + 1) == '=') || \
			(ft_strncmp(temp1->next->var, v, ft_strlen(v) + 1) == '\0'))
		{
			temp2 = temp1->next->next;
			free(temp1->next->var);
			free(temp1->next);
			temp1->next = temp2;
			return ;
		}
		temp1 = temp1->next;
	}
}

static void	delete_list_envp(t_envp **list, char *var)
{
	t_envp	*temp1;
	t_envp	*temp2;
	char	*v;

	if (!list)
		return ;
	temp1 = *list;
	temp2 = NULL;
	v = find_var_name(var);
	delete_cycle(temp1, temp2, v, list);
	free(v);
}

static int	unset_check(char *temp, char **var)
{
	if (*temp >= '0' && *temp <= '9')
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(*var, 2);
		ft_putstr_fd("' is a wrong variable\n", 2);
		return (1);
	}
	while (*temp)
	{
		if (!((*temp >= '0' && *temp <= '9') || (*temp >= 'a' && \
		*temp <= 'z') || (*temp >= 'A' && *temp <= 'Z') || *temp == '_'))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd("' is a wrong variable\n", 2);
			return (1);
		}
		temp++;
	}
	return (0);
}

int	ft_unset(t_data	*data, char **var, char ***envp)
{
	char	*temp;
	int		flag;

	var++;
	flag = 0;
	while (*var)
	{
		temp = *var;
		if (unset_check(temp, var))
		{
			var++;
			flag = 1;
			continue ;
		}
		delete_list_envp(&(data->env), *var);
		delete_list_envp(&(data->exp), *var);
		var++;
	}
	refresh_envp(data->env, envp);
	return (flag);
}
