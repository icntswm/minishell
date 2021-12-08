// void	check_save_array_and_new(char *new, char *old, char **str)
// {
// 	printf("new: %s|old: %s\n", new, old);
// 	int i;
// 	// int j;
// 	int start = 0;
// 	// int counter;
// 	char *save;
// 	char *save_in_quot;
	
// 	// counter = 0;
// 	i = 0;
// 	// j = 0;
// 	save = NULL;
// 	save_in_quot = NULL;
// 	while (i < ft_strlen(old))
// 	{
// 		if (old[i] == 34)
// 		{
// 			start = i;
// 			i = skip_quotes(old, 34, i);
// 			i++;
// 			while (old[i] && old[i] != ' ' && old[i] != 34 && old[i] != 39)
// 				i++;
// 			save_in_quot = ft_substr(old, start, i - start);
// 			if (old[i] == 39 || old[i] == 34)
// 				i--;
// 			save = *str;
// 			*str = ft_strjoin(save, save_in_quot);
// 			free(save);
// 			free(save_in_quot);
// 		}
// 		else if (old[i] == 39)
// 		{
// 			start = i;
// 			i = skip_quotes(old, 39, i);
// 			i++;
// 			while (old[i] && old[i] != ' ' && old[i] != 34 && old[i] != 39)
// 				i++;
// 			save_in_quot = ft_substr(old, start, i - start);
// 			if (old[i] == 39 || old[i] == 34)
// 				i--;
// 			save = *str;
// 			*str = ft_strjoin(save, save_in_quot);
// 			free(save);
// 			free(save_in_quot);
// 		}
// 		else if (old[i] != 34 && old[i] != 39 && old[i] != ' ')
// 		{
// 			start = i;
// 			// counter++;
// 			while (old[i] && old[i] != ' ')
// 				i++;
// 			save_in_quot = ft_substr(old, start - 1, (i + 1) - start);
// 			save = *str;
// 			*str = ft_strjoin(save, save_in_quot);
// 			free(save);
// 			free(save_in_quot);
// 		}
// 		i++;
// 		printf("lol|->NEW: %s\n", *str);
// 	}
// 	// printf("COUNTER: %d|%s\n", counter, *str);
// 	// return (counter);
// }

// char	*hand_single_and_double_quotes(char *str)
// {
// 	int i;
// 	char *save1;
// 	char *save2;
// 	int start = 0;
// 	char *new;
// 	int check = 0;
	
// 	i = 0;
// 	new = NULL;
// 	save1 = NULL;
// 	save2 = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == 34)
// 		{
// 			if (new == NULL)
// 				new = ft_substr(str, 0, i);
// 			i++;
// 			while (str[i] && str[i] != 34)
// 			{
// 				start = i;
// 				while (str[i] && str[i] != ' ' && str[i] != 34)
// 					i++;
// 				if (str[i] == ' ')
// 				{
// 					while (str[i] && str[i] == ' ')
// 						i++;
// 					save2 = ft_substr(str, start, i - start);
// 				}
// 				else if (str[i] == 34)
// 					save2 = ft_substr(str, start, i - start);
// 				else if (str[i] == '\0')
// 					save2 = ft_substr(str, start, i - start);
// 				if (save2)
// 				{
// 					save1 = ft_strjoin(new, "\"");
// 					new = ft_strjoin(save1, save2);
// 					free(save1);
// 					free(save2);
// 					save1 = new;
// 					new = ft_strjoin(save1, "\"");
// 					free(save1);
// 					if (str[i] != 34)
// 					{
// 						save2 = new;
// 						new = ft_strjoin(save2, " ");
// 						free(save2);
// 					}
// 				}
// 			}
// 			if (str[i] == 34)
// 			{
// 				i++;
// 				start = i;
// 				while (str[i] && str[i] != 34)
// 					i++;
// 				save1 = new;
// 				save2 = ft_substr(str, start, i - start);
// 				if (str[i] == 34)
// 					i--;
// 				new = ft_strjoin(save1, save2);
// 				free(save1);
// 				free(save2);
// 			}
// 		}
// 		else if (str[i] == 39)
// 			i = skip_quotes(str, 39, i);
// 		i++;
// 	}
// 	printf("---NEW---|%s|check: %d\n", new, check);
// 	if (new)
// 	{
// 		free(str);
// 		return(new);
// 	}
// 	return(str);
// }

// int	check_space_argv(t_data *data, char ***arr, int size, char **save_array)
// {
// 	int i;
// 	char **array;
// 	char **new;
// 	char *new_str;
// 	int count;
// 	char *save;
	
// 	i = 0;
// 	count = 0;
// 	new_str = NULL;
// 	if (ft_strncmp(*arr[i], "export", 6) != 0)
// 	{
// 		while (i < size)
// 		{
// 			save = save_array[i];
// 			save_array[i] = check_dollar(&(*data), save, ft_strlen(save), 0);
// 			i++;
// 		}
// 		array = *arr;
// 		i = 0;
// 		while (i < size)
// 		{
// 			check_save_array_and_new(array[i], save_array[i], &new_str);
// 			save = new_str;
// 			new_str = ft_strjoin(save, " ");
// 			free(save);
// 			i++;
// 		}
// 		i = 0;
// 		printf("new_str: %s\n", new_str);
// 		while (i < ft_strlen(new_str))
// 		{
// 			if (new_str[i] == 34)
// 			{
// 				printf("1:%d|%c\n", i, new_str[i]);
// 				i++;
// 				while (new_str[i] && new_str[i] != 34)
// 				{
// 					while (new_str[i] && new_str[i] != ' ' && new_str[i] != 34)
// 						i++;
// 					if (new_str[i] == ' ')
// 					{
// 						count++;
// 						while (new_str[i] && new_str[i] == ' ')
// 							i++;
// 					}
// 					// if (new_str[i] == 34 || new_str[i] == 39)
// 					// {
// 					// 	i--;
// 					// 	break ;
// 					// }
// 				}
// 				printf("2:%d|%c\n", i, new_str[i]);
// 			}
// 			else if (new_str[i] == 39)
// 			{
// 				i = skip_quotes(new_str, 39, i);
// 				printf("3:%d|%c\n", i, new_str[i]);
// 				if (i == -1)
// 				{
// 					count++;
// 					break ;
// 				}
// 			}
// 			else if (new_str[i] == ' ')
// 			{
// 				printf("4%d|%c\n", i, new_str[i]);
// 				count++;
// 				while (new_str[i] && new_str[i] == ' ')
// 					i++;
// 				if (new_str[i] == 34 || new_str[i] == 39)
// 					i--;
// 			}
// 			else if (new_str[i] == '\0')
// 				count++;
// 			i++;
// 		}
// 		new_str = hand_single_and_double_quotes(new_str);
// 		printf("count: %d\n%s\n", count, new_str);
// 		int start = 0;
// 		i = 0;
// 		int j = 0;
// 		if (count != size)
// 		{
// 			new = (char **)malloc(sizeof(char *) * (count + 1));
// 			while (j < count)
// 			{
// 				while (i <= ft_strlen(new_str))
// 				{
// 					if (new_str[i] == 34)
// 						i = skip_quotes(new_str, 34, i);
// 					else if (new_str[i] == 39)
// 						i = skip_quotes(new_str, 39, i);
// 					if ((new_str[i] == ' ' || new_str[i] == '\0') && (i - start) > 1)
// 					{
// 						new[j] = ft_substr(new_str, start, i - start);
// 						new[j] = handling_quotes_inred(new[j]);
// 						save = new[j];
// 						new[j] = ft_chartrim(save, ' ');
// 						free(save);
// 						// printf("new[%d]: %s\n", j, new[j]);
// 						j++;
// 						while (new_str[i] && new_str[i + 1] == ' ')
// 							i++;
// 						start = i;
// 					}
// 					i++;
// 				}
// 			}
// 			new[j] = NULL;
// 			clean_array(*arr, size);
// 			*arr = new;
// 		}
// 		free(new_str);
// 		return(count);
// 	}
// 	return(size);
	
// }

// void	make_error_ambiguos(t_data *data, char *var)
// {
// 	int i;
// 	char *save1;
// 	char *save2;
	
// 	save1 = NULL;
// 	save2 = NULL;
// 	i = 0;
// 	while (var[i] && var[i] != '=')
// 		i++;
// 	save1 = ft_substr(var, 0, i);
// 	save2 = ft_strjoin("$", save1);
// 	free(save1);
// 	data->error = ft_strjoin(save2, ": ambiguous redirect");
// 	free(save2);
// }

// void	check_space_list(t_data *data, t_files *list, char redrct)
// {
// 	t_files *p;
// 	void	*save;
// 	int i;
// 	int col_list;
// 	int	col_space;
// 	char *save_name;

// 	p = list;
// 	save = p;
// 	col_list = 0;
// 	while (p != NULL)
// 	{
// 		col_list++;
// 		if (redrct == '<' && p->mode == 2)
// 			col_list--;
// 		p = p->next;
// 	}
// 	i = 0;
// 	col_space = 0;
// 	p = save;
// 	while (p != NULL)
// 	{
// 		i = ft_strlen(p->filename) - 1;
// 		if ((redrct == '<' && p->mode != 2) || redrct == '>')
// 		{
// 			if (p->filename[i] == ' ')
// 				while (i >= 0 && p->filename[i] == ' ')
// 					i--;
// 			while (i >= 0)
// 			{
// 				if (p->filename[i] != ' ')
// 				{
// 					// printf("i: %c\n", p->filename[i]);
// 					col_space++;
// 					save_name = p->filename;
// 					while (i >= 0 && p->filename[i] != ' ')
// 						i--;
// 				}
// 				i--;
// 			}
// 		}
// 		p = p->next;
// 	}
// 	if (col_list != col_space)
// 	{
// 		i = 0;
// 		t_envp	*q;
// 		q = data->env;
// 		int j = 0;
// 		int k = 0;
// 		while (q != NULL)
// 		{
// 			j = ft_strlen(q->var) - 1;
// 			while (j >= 0)
// 			{
// 				k = ft_strlen(save_name) - 1;
// 				if (q->var[j] == save_name[k])
// 				{
// 					while (j >= 0 && k >= 0 && q->var[j] == save_name[k])
// 					{
// 						j--;
// 						k--;
// 						if (k == 0 && q->var[j - 1] == '=')
// 							make_error_ambiguos(&(*data), q->var);
// 					}
// 				}
// 				j--; 
// 			}
// 			q = q->next;
// 		}
// 	}
// }