#include "minishell.h"

char	*dollar_and_end_line(char *str, char *new, int i)
{
	char	*save1;
	char	*save_new;

	save1 = NULL;
	save_new = NULL;
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
	return (new);
}

int	dollar_question(int i, char *str, char **new)
{
	char	*save1;
	char	*save2;
	char	*save3;
	int		start;

	save1 = ft_itoa(g_question);
	start = ++i;
	while (str[i] && str[i] != '$')
		i++;
	save2 = ft_substr(str, start, i - start);
	save3 = *new;
	*new = ft_strjoin(save3, save1);
	free(save3);
	save3 = *new;
	*new = ft_strjoin(save3, save2);
	free(save3);
	free(save1);
	free(save2);
	if (str[i] == '$')
		i--;
	return (i);
}

int	dollar_pid(t_data *data, int i, char *str, char **new)
{
	char	*save1;
	char	*save2;
	char	*save3;
	int		start;

	start = ++i;
	save1 = ft_itoa(data->get_pid);
	while (str[i] && str[i] != '$')
		i++;
	save2 = ft_substr(str, start, i - start);
	save3 = *new;
	*new = ft_strjoin(save3, save1);
	free(save3);
	save3 = *new;
	*new = ft_strjoin(save3, save2);
	free(save3);
	free(save1);
	free(save2);
	if (str[i] == '$')
		i--;
	return (i);
}
