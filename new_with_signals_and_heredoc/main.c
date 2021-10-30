#include "minishell.h"

// t_envp  *list_envp(t_envp *list, char *str_env)
// {
// 	t_envp	*new_list;
// 	void	*save;

// 	if (!list)
// 	{
// 		list = (t_envp *)malloc(sizeof(t_envp));
// 		list->var = str_env;
// 		list->next = NULL;
// 	}
// 	else
// 	{
// 		save = list;
// 		new_list = (t_envp *)malloc(sizeof(t_envp));
// 		while (list->next != NULL)
// 			list = list->next;
// 		list->next = new_list;
// 		list = save;
// 		new_list->var = str_env;
// 		new_list->next = NULL;
// 	}
// 	return (list);
// }

// void	envp_print(t_envp *list, int pointer)
// {
// 	t_envp *p;

// 	p = list;
// 	while (p != NULL)
// 	{
// 		if (pointer == 1)
// 			printf("declare -x ");
// 		printf("%s\n", p->var);
// 		p = p->next;
// 	}
// }

// t_envp	*make_envp(t_envp *list, char **envp)
// {
// 	t_envp *p;
// 	void	*save;
// 	int i;

// 	i = 0;
// 	p = list;
// 	while (envp[i])
// 	{
// 		p = list_envp(p, envp[i]);
// 		i++;
// 	}
// 	return (p);
// }

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
		tmp[i] = ft_strdup(envp[i]), i++;
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
		temp = temp->next, i++;
	free_array(*envp);
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	while (env)
		new[i] = ft_strdup(env->var), i++, env = env->next;
	new[i] = NULL;
	*envp = new;
	return (new);
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int		i;
	int		status;

	envp = make_new_envp(envp);
	init_data(&data, &envp);
	status = 0;
	i = 0;

	signal(SIGQUIT, ctrl_slash);
	signal(SIGINT, ctrl_c);

	while (isatty(0))
	{
        data.line = readline("minishell$ ");
        add_history(data.line);
		if (!data.line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (data.line[0] != '\0')
		{
            parser(&data);
			if (data.error == NULL)
				status = pipex(&data, &envp);
			else
			{
				unlink_here_doc_files(&data);
				free(data.error);
			}
		}
		else
			free(data.line);
		i++;
    }
	free_array(envp);// + clean lists env and exp
	return (0);
	// clean_export(data.exp);
}