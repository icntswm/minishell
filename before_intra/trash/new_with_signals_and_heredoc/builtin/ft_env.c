#include "../minishell.h"

int	ft_env(t_data *data, char	**cmd)
{
	t_envp	*env;

	if (cmd[1])
	{
		ft_putstr_fd("Minishell does not support options for env.\n", 2);
		free_array(cmd);
		return (1);
	}
	env = data->env;
	while(env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	free_array(cmd);
	return (0);
}
