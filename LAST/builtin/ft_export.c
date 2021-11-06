#include "../minishell.h"

static int	check_is_there_value(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '=')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": wrong variable.\n", 2);
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	check_existance(t_envp *list, char *var)
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

static int	change_list_envp(t_envp *temp1, char *var)
{
	char	*v;

	if (!temp1)
		return (0);
	v = find_var_name(var);
	if ((ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '=') || \
		(ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '\0'))
	{
		free(temp1->var);
		temp1->var = ft_strdup(var);
		free(v);
		return (1);
	}
	while (temp1->next)
	{
		if ((ft_strncmp(temp1->next->var, v, ft_strlen(v) + 1) == '=') || \
			(ft_strncmp(temp1->next->var, v, ft_strlen(v) + 1) == '\0'))
		{
			free(temp1->next->var);
			temp1->next->var = var;
			free(v);
			return (1);
		}
		temp1 = temp1->next;
	}
	free(v);
	return (0);
}

static int	export_cycle(char *str, int res, t_data *data, char **cmd)
{
	char	*save_str;

	save_str = NULL;
	if (res == -1)
		return (1);
	if (res == 0)
	{
		if (!check_existance(data->exp, *cmd))
		{
			str = ft_strdup(*cmd);
			if (!change_list_envp(data->exp, str))
			{
				add_list_envp(data->exp, str);
				free(str);
			}
		}
	}
	else
	{
		str = ft_strdup(*cmd);
		save_str = ft_strdup(*cmd);
		if (!change_list_envp(data->exp, str))
		{
			add_list_envp(data->exp, str);
			free(str);
		}
		if (!change_list_envp(data->env, save_str))
		{
			add_list_envp(data->env, save_str);
			free(save_str);
		}	
	}
	return (0);
}

int	ft_export(t_data *data, char **cmd, char ***envp)
{
	char	*str;
	int		res;
	char	**temp;
	int		status;

	cmd++;
	if (!*cmd)
		return (print_export(data));
	status = 0;
	while (*cmd)
	{
		res = check_is_there_value(*cmd);
		status = export_cycle(str, res, data, cmd);
		cmd++;
	}
	if (status == 1)
		make_heredoc_question_error(1);
	else
		make_heredoc_question_error(0);
	refresh_envp(data->env, envp);
	return (status);
}
