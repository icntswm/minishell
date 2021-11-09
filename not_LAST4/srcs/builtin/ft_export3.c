/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:18:55 by squickfi          #+#    #+#             */
/*   Updated: 2021/11/09 18:21:54 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_there_value(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '=')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' is a wrong variable.\n", 2);
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		if (str[0] >= '0' && str[0] <= '9')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("' wrong variable\n", 2);
			return (-1);
		}
		else
		{
			if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] \
				<= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd("' wrong variable\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	check_existance(t_envp *list, char *var)
{
	char	*var_name;

	var_name = find_var_name(var);
	while (list)
	{
		if ((ft_strncmp(list->var, var_name, \
			ft_strlen(var_name) + 1) == '\0') || \
			(ft_strncmp(list->var, var_name, ft_strlen(var_name) + 1) == '='))
		{
			free(var_name);
			return (1);
		}
		list = list->next;
	}
	free(var_name);
	return (0);
}

char	**make_new_envp(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc((i + 1) * sizeof(char *));
	if (!tmp)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**refresh_envp(t_envp *env, char ***envp)
{
	t_envp	*temp;
	char	**new;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	free_array(*envp);
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	while (env)
	{
		new[i] = ft_strdup(env->var);
		i++;
		env = env->next;
	}
	new[i] = NULL;
	*envp = new;
	return (new);
}

void	free_list_envp(t_envp *list)
{
	t_envp	*p;
	void	*save;

	p = list;
	while (p != NULL)
	{
		save = p->next;
		free(p);
		p = save;
	}
}
