#include "../minishell.h"

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

int	ft_unset(t_data	*data, char **var, char ***envp)
{
	char	**temp_for_free;
	char	*temp;

	temp_for_free = var;
	var++;
	while (*var)
	{
		temp = *var;
		while (*temp && *temp != '=')
			temp++;
		if (*temp == '=')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd(": wrong variable.\n", 2);
			var++;
			continue ;
		}
		delete_list_envp(&(data->env), *var);
		delete_list_envp(&(data->exp), *var);
		var++;
	}
	refresh_envp(data->env, envp);
	make_heredoc_question_error(0);
	return (0);
}
