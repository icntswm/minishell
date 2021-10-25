#	include "minishell.h"

char	*check_dollar(t_data *data, char *str)
{
	int i = 0;
	char *save1 = NULL;
	char *save2 = NULL;
	int len_str = ft_strlen(str);

	// не работает если строка будет типо: $PATHlol (надо искать будет переменную в массивах экспорта и локальных) 
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (i - 1 != 0)
				save1 = ft_substr(str, 0, i - 1);
			while (str[i] && str[i] != 34 && str[i] != 39 && str[i] != '$')
				i++;
			printf("i: %d len_str: %d\n", i, len_str);
			if (i != len_str)
				save2 = ft_substr(str, i, len_str - i);
			free(str);
			str = ft_strjoin(save1, "ABOBA");
			free(save1);
			if (i != len_str)
			{
				str = ft_strjoin(str, save2);
				free(save2);
			}
			if (str[i] == '$')
				i--;
			// break;
		}
		i++;
	}
	return (str);
}

int	it_quotes(t_data *data, char **new, char *str, int i)
{
	int start;
	int quot;
	char *save1;
	char *save3;

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
			save1 = check_dollar(&(*data), save1);
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
	save1 = check_dollar(&(*data), save1);
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
	free(str);
	return (new);
}

