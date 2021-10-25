#	include "minishell.h"

int compare_dollar_and_exp(char *exp, char *dollar)
{
	int i;

	i = 0;
	while(exp[i] && exp[i] != '=')
	{
		if (exp[i] != dollar[i])
			return(1);
		i++;
	}
	if (dollar[i] != '\0')
		return (1);
	return (0);
}

char	*search_envp_dollar(t_data *data, char *dollar)
{
	t_envp *p;
	int i;

	i = 0;
	p = data->exp;
	while (p != NULL)
	{
		if (compare_dollar_and_exp(p->var, dollar) == 0)
		{
			// printf("ok\n");
			while (p->var[i] && p->var[i] != '=')
				i++;
			free(dollar);
			dollar = ft_substr(p->var, i + 2, ft_strlen(p->var) - (i + 3));
			return (dollar);
		}		
		p = p->next;
	}
	free(dollar);
	return (ft_strdup(""));
}

char	*check_dollar(t_data *data, char *str, int lenght_str, int cmd_len)
{
	int i = 0;
	char *save1 = NULL;
	char *save2 = NULL;
	int len_str = ft_strlen(str);
	char *new;
	char *save_new = NULL;
	char *dollar = NULL;
	int start = 0;

	new = NULL;
	
	// printf("LEN_STR: %d cmd_len: %d\n", lenght_str, cmd_len);
	printf("str: |%s|\n", str);
	// не работает если строка будет типо: $PATHlol (надо искать будет переменную в массивах экспорта и локальных) 
	while (i < ft_strlen(str))
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			i++;
			start = i;
			if (new == NULL)
			{
				save1 = ft_substr(str, 0, i - 1);
				save_new = new;
				new = ft_strjoin(save_new, save1);
				free(save_new);
				free(save1);
			}	
			while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != 39 && str[i] != '|' && str[i] > 47)
				i++;
			dollar = ft_substr(str, start, i - start);
			// printf("dollar: %s\n", dollar);
			dollar = search_envp_dollar(&(*data), dollar);
			// printf("dollar: %s\n", dollar);
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			if (i != start)
				save2 = ft_substr(str, start, i - start);
			save_new = new;
			new = ft_strjoin(save_new, dollar);
			free(dollar);
			free(save_new);
			if (i != start)
			{
				save_new = new;
				new = ft_strjoin(save_new, save2);
				free(save_new);
				free(save2);
			}
			if (str[i] == '$')
				i--;
		}
		else if (str[i] == '$' && str[i + 1] == '\0' && cmd_len + i == lenght_str - 1)
		{
			if (new == NULL)
			{
				save1 = ft_substr(str, 0, i + 1);
				save_new = new;
				new = ft_strjoin(save_new, save1);
				free(save_new);
				free(save1);
			}
			else
			{
				save_new = new;
				new = ft_strjoin(save_new, "$");
				free(save_new);
			}
		}
		i++;
	}
	i = 0;
	if (new != NULL)
	{
		free(str);
		// printf("new: |%s|\n", new);
		return(new);
	}
	else
	{
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] == '\0')
			{
				save_new = str;
				str = ft_substr(save_new, 0, i);
				// printf("STRRRRR: |%s|\n", str);
				free(save_new);
				break ;
			}
			i++;
		}
	}
	return (str);
}

int	it_quotes(t_data *data, char **new, char *str, int i)
{
	int start;
	int quot;
	char *save1;
	char *save3;
	char *save2;

	save1 = NULL;
	save3 = NULL;
	start = i - 1;
	if (str[i - 1] == 34)
		quot = 34;
	else if (str[i - 1] == 39)
		quot = 39;
	while (str[i] && str[i] != quot)
		i++;
	if (i - (start + 1) > 0)
	{
		save1 = ft_substr(str, start + 1, i - (start + 1));
		if (quot == 34)
			save1 = check_dollar(&(*data), save1, ft_strlen(str), start);
		save3 = *new;
		*new = ft_strjoin(save3, save1);
		free(save3);
		free(save1);
	}
	return (i);
}

int	not_quotes(t_data *data, char **new, char *str, int i)
{
	int start;
	char *save1 = NULL;
	char *save3 = NULL;

	start = i;
	while (str[i] && str[i] != 34 && str[i] != 39)
		i++;
	save1 = ft_substr(str, start, i - start);
	save1 = check_dollar(&(*data), save1, ft_strlen(str), start);
	save3 = *new;
	*new = ft_strjoin(save3, save1);
	free(save3);
	free(save1);
	return (i);
}

char	*help_quot(t_data *data, char *str, char *new, int i)
{
	int start;

	start = 0;
	while (str[i])
	{
		start = i;
		if (str[i] == 34)
			i = it_quotes(&(*data), &new, str, ++i);
		else if (str[i] == 39)
			i = it_quotes(&(*data), &new, str, ++i);
		if (str[i] != 34 && str[i] != 39)
		{
			i = not_quotes(&(*data), &new, str, i);
			i--;
		}
		i++;
	}
	return (new);
}

char	*ft_quot(t_data *data, char *str)
{
    int i;
	char *new;

    i = 0;
	new = NULL;
    if (str[0] == 34 || str[0] == 39)
    {
        if (str[0] == 34)
            i = skip_quotes(str, 34, i);
        else
            i = skip_quotes(str, 39, i);
        if (str[i + 1] == ' ')
        {
            i++;
            new = ft_substr(str, 0, i);
        }
        else
            i = 0;
    }
	new = help_quot(&(*data), str, new, i);
	// printf("new: %s\n", new);
	free(str);
	return (new);
}

