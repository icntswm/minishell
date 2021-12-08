#include "minishell.h"

t_envp	*add_list_envp(t_envp *list, char *str)
{
	t_envp	*new_list;
	void	*save;
	char	*str_env;

	str_env = ft_strdup(str);
	if (!list)
	{
		list = (t_envp *)malloc(sizeof(t_envp));
		list->var = str_env;
		list->next = NULL;
	}
	else
	{
		save = list;
		new_list = (t_envp *)malloc(sizeof(t_envp));
		while (list->next != NULL)
			list = list->next;
		list->next = new_list;
		list = save;
		new_list->var = str_env;
		new_list->next = NULL;
	}
	return (list);
}

t_envp	*make_envp(t_envp *list, char **envp)
{
	t_envp	*p;
	int		i;

	i = 0;
	p = list;
	while (envp[i])
	{
		p = add_list_envp(p, envp[i]);
		i++;
	}
	return (p);
}

void	init_data(t_data *data, char ***envp)
{
	t_envp	*shlvl_str;
	char	*shlvl_str_temp;
	int		shlvl;

	data->env = NULL;
	data->exp = NULL;
	data->env = make_envp(data->env, *envp);
	data->exp = make_envp(data->exp, *envp);
	export_str(data, "SHELL", "./minishell", envp);
	shlvl_str = data->env;
	while (shlvl_str)
	{
		if (ft_strncmp(shlvl_str->var, "SHLVL=", 6) == 0)
		{
			shlvl_str_temp = ft_strchr(shlvl_str->var, '=') + 1;
			shlvl = ft_atoi(shlvl_str_temp) + 1;
			shlvl_str_temp = ft_itoa(shlvl);
			export_str(data, "SHLVL", shlvl_str_temp, envp);
			free(shlvl_str_temp);
			return ;
		}
		shlvl_str = shlvl_str->next;
	}
	export_str(data, "SHLVL", "1", envp);
}
