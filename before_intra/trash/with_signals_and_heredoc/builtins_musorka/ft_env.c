#include "../minishell.h"

t_envp  *list_envp(t_envp *list, char *str_env)
{
	t_envp	*new_list;
	void	*save;

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

void	envp_print(t_envp *list, int pointer)
{
	t_envp *p;

	p = list;
	while (p != NULL)
	{
		if (pointer == 1)
			printf("declare -x ");
		printf("%s\n", p->var);
		p = p->next;
	}
}

t_envp	*make_envp(t_envp *list, char **envp)
{
	t_envp *p;
	void	*save;
	int i;

	i = 0;
	p = list;
	while (envp[i])
	{
		p = list_envp(p, envp[i]);
		i++;
	}
	return (p);
}

void	clean_envp(t_envp *list)
{
	t_envp *p;
	void	*save;

	p = list;
	while (p != NULL)
	{
		save = p->next;
		free(p);
		p = save;
	}
}

void	ft_env(t_data *data)
{
	envp_print(data->env, 0);
	clean_envp(data->env);
}