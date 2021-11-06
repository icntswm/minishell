#include "../minishell.h"

int	ft_env(t_data *data, char	**cmd)
{
	t_envp	*env;

	if (cmd[1])
	{
		ft_putstr_fd("Minishell does not support options for env.\n", 2);
		make_heredoc_question_error(127);
		return (127);
	}
	env = data->env;
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	make_heredoc_question_error(0);
	return (0);
}
