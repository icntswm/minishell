#include "minishell.h"

// void    make_envp(t_data *data, char **envp)
// {
//     int i;

//     i = 0;
//     data->envp = NULL;
//     while (envp[i])
//     {
//         data->envp = list_envp(data->envp, envp[i]);
// 		i++;
//     }
    
// }

// void	del_envp(t_data *data, char *delete)
// {
// 	t_envp	*p;
// 	void	*save;
// 	void	*save_n;

// 	p = data->envp;
// 	while (p != NULL)
// 	{
// 		if (ft_strncmp(p->var, delete, ft_strlen(delete)) == 0)
// 		{
// 			printf("nashel-------------------------\n");
// 			save_n = p->next;
// 			free(p);
// 			p = save;
// 			p->next = save_n;
// 		}
// 		save = p;
// 		p = p->next;
// 	}
	
// }

// void	add_envp(t_data *data, char *add)
// {
// 	data->envp = list_envp(data->envp, add);
// }


int main(int argc, char **argv, char **envp)
{
    t_data data;
    int i = 0;

    // make_envp(&data, envp);
	// printf("kekos----------------------------------------------------\n");
	// envp_print(&data);
	// del_envp(&data, "LC_TIME");
	// envp_print(&data);
	// add_envp(&data, "hello=2");
	// envp_print(&data);


	data.env = NULL;
	data.exp = NULL;
	// data.env = make_envp(data.env, envp);
	data.exp = make_envp(data.exp, envp);
	
	// ft_env(&data);
	ft_export(&data);

	
    // while (i < 2)
    // {
    //     data.line = readline("minishell$ ");
    //     // if (data.line)
    //         parser(&data);
    //     i++;
    // }
}