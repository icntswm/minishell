#include "minishell.h"

int	help_change_list_envp(t_envp *temp1, char *v, char *var)
{
	if ((ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '=') || \
		(ft_strncmp(temp1->var, v, ft_strlen(v) + 1) == '\0'))
	{
		free(temp1->var);
		temp1->var = var;
		free(v);
		return (1);
	}
	return (0);
}

int	change_list_envp(t_envp *temp1, char *var)
{
	char	*v;

	if (!temp1)
		return (0);
	v = find_var_name(var);
	if (help_change_list_envp(temp1, v, var) == 1)
		return (1);
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

void	help_export_cycle(t_data *data, char *str, char **cmd)
{
	char	*save_str;

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

int	export_cycle(int res, t_data *data, char **cmd)
{
	char	*str;

	str = NULL;
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
		help_export_cycle(data, str, cmd);
	return (0);
}

int	ft_export(t_data *data, char **cmd, char ***envp)
{
	int		res;
	int		status;

	cmd++;
	if (!*cmd)
		return (print_export(data));
	status = 0;
	while (*cmd)
	{
		res = check_is_there_value(*cmd);
		status = export_cycle(res, data, cmd);
		cmd++;
	}
	refresh_envp(data->env, envp);
	return (status);
}
