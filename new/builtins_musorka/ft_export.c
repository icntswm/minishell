#include "../minishell.h"

char	*help_make_quotes(char *str, int i)
{
	char *save1;
	char *save2;
	char *save3;
	char *new;

	save1 = ft_substr(str, 0, i + 1);
	save2 = ft_substr(str, i + 1, ft_strlen(str));
	save3 = ft_strjoin(save1, "\"");
	free(save1);
	save1 = ft_strjoin(save3, save2);
	free(save2);
	free(save3);
	new = ft_strjoin(save1, "\"");
	free(save1);
	return (new);
}

void	make_quotes_export(t_data *data)
{
	t_envp *p;
	int i;

	p = data->exp;
	while (p != NULL)
	{
		i = 0;
		while (p->var[i])
		{
			if (p->var[i] == '=' && p->var[i + 1] != 34)
			{
				p->var = help_make_quotes(p->var, i);
				break ;
			}
			i++;
			if (i == ft_strlen(p->var) - 1)
				p->var = ft_strdup(p->var);

		}
		p = p->next;		
	}
}

void clean_export(t_envp *list)
{
	t_envp *p;
	void	*save;

	p = list;
	while (list != NULL)
	{
		save = list->next;
		free(list->var);
		free(list);
		list = save;
	}
	printf("\n\n\n\n\n");
	// envp_print(p, 1);

}

void	ft_export(t_data *data)
{
	make_quotes_export(&(*data));
	// envp_print(data->exp, 1);
	// clean_export(data->exp);
}