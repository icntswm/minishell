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

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int i = 0;

	// data.env = NULL;
	// data.exp = NULL;
	// // data.env = make_envp(data.env, envp);
	// data.exp = make_envp(data.exp, envp);
	
	// // ft_env(&data);
	// ft_export(&data);

    while (i < 1)
    {
        data.line = readline("minishell$ ");
        // if (data.line)
            parser(&data);
        i++;
    }
	// clean_export(data.exp);
	
}