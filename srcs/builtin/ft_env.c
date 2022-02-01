#include "minishell.h"

int	ft_env(t_data *data, char	**cmd)
{
	t_envp	*env;

	if (cmd[1])
	{
		ft_putstr_fd("minishell: shell does not supp\
ort options for env.\n", 2);
		return (228);
	}
	env = data->env;
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (0);
}
