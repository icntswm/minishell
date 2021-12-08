#include "../minishell.h"

int	export_str(t_data *data, char *var, char *value, char ***envp)
{
	char	**cmd;
	char	*str;
	int		i;
	int		j;

	cmd = malloc(3 * sizeof(char *));
	str = malloc((ft_strlen(var) + ft_strlen(value) + 2) * sizeof(char));
	if (!cmd || !str)
		return (1);
	i = 0;
	j = 0;
	while (var[j])
		str[i] = var[j], i++, j++;
	str[i] = '=', i++, j = 0;
	while (value[j])
		str[i] = value[j], i++, j++;
	str[i] = '\0';
	cmd[0] = ft_strdup("export");
	cmd[1] = str;
	cmd[2] = NULL;
	ft_export(data, cmd, envp);
	return (0);
}

char	*find_var_name(char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

static void	print_export_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		ft_putchar_fd(str[i], 1), i++;
	if (str[i] == '=')
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		i++;
		while (str[i])
		{
			if (str[i] == '\"')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(str[i], 1);
			i++;
		}
		ft_putchar_fd('\"', 1);
	}
}

int	print_export(t_data *data)
{
	t_envp	*exp;

	exp = data->exp;
	while(exp)
	{
	// ft_putstr_fd("!!!", 2);
		ft_putstr_fd("declare -x ", 1);
		print_export_str(exp->var);
		ft_putchar_fd('\n', 1);
		exp = exp->next;
	}
	return (0);
}
