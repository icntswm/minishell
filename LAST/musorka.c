// void	make_name_herequest(char *str, t_data *data)
// {
// 	char *save1;
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	save1 = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
// 	data->name_herequest = ft_strjoin("heredoc_quest_error", save1);
// 	free(save1);
// 	printf("herequest: %s\n", data->name_herequest);
// }

// void dollar_question(char *str, char **new, t_data *data)
// {
// 	char *save1;
// 	char *save2;
// 	int file;

// 	t_envp *p;

// 	p = data->env;
// 	while (p != NULL)
// 	{
// 		if (ft_strncmp(p->var, "SHLVL=", ft_strlen("SHLVL=")) == 0)
// 			break ;
// 		p = p->next;
// 	}
// 	if (data->name_herequest == NULL)
// 		make_name_herequest(p->var, &(*data));
// 	if (access(data->name_herequest, F_OK) == 0)
// 	{
// 		file = open("heredoc_quest_error", O_RDONLY, 0644);
// 		get_next_line(file, &save1);
// 		close(file);
// 		unlink("heredoc_quest_error");
// 	}
// 	else
// 		save1 = ft_itoa(question);
// 	question = 127;
// 	save2 = ft_substr(str, 2, ft_strlen(str));
// 	*new = ft_strjoin(save1, save2);
// 	free(save1);
// 	free(save2);
// }




// bonus ||
// void    check_double_pipe(t_data *data)
// {
//     int i;
//     char *save;

// 	i = 0;
//     save = NULL;
// 	while (i < ft_strlen(data->line))
// 	{
// 		if (data->line[i] == 34)
// 			i = skip_quotes(data->line, 34, i);
// 		else if (data->line[i] == 39)
// 			i = skip_quotes(data->line, 39, i);
//         else if (data->line[i] == '|' && data->line[i + 1] == '|'
//             && data->line[i + 2] == '|')
//             ft_error(&(*data), "pipe");
//         else if (data->line[i] == '|'&& data->line[i + 1] == '|'
//             && data->line[i + 2] != '|')
//         {
//             if (i == 0 || data->line[i + 2] == '\0')
//             {
//                 ft_error(&(*data), "double_pipe");
//                 break ;
//             }
//             save = data->line;
//             data->line = ft_substr(save, 0, i);
//             free(save);
//             break ;
//         }
//         if (data->error)
//             break ;
//         if (i == -1)
// 		{
// 			ft_error(&(*data), "quotes");
// 			break ;
// 		}
//         i++;
// 	}
// }


//bonus *
// int    search_col_star(char *str, t_pos *list)
// {
//     t_pos *p;
//     int i;
//     int col;
//     int star_in_quotes;

//     i = 0;
//     col = 0;
//     star_in_quotes = 0;
//     p = list;
//     while (str[i])
//     {
//         if (str[i] == 34)
//         {
//             if (i != 0 && str[i - 1] == ' ')
//             {
//                 col++;
//                 printf("it_is_star: |%d|%c|\n", i, str[i]);
//             }
// 			i = skip_quotes(str, 34, i);
//             if (str[i] != ' ')
//             {
//                 while (str[i] && str[i] != ' ')
//                     i++;
//             }
//         }
//         else if (str[i] == 39)
// 		{
//         	i = skip_quotes(str, 39, i);
//             if (str[i] != ' ')
//             {
//                 while (str[i] && str[i] != ' ')
//                     i++;
//             }
//         }
//         else if (str[i] == '*')
//         {
//             col++;
//             if (i != 0 && str[i - 1] != ' ')
//             {
//                 while (i >= 0 && str[i - 1] != ' ')
//                     i--;
//             }
//             printf("it_is_star: |%d|%c|\n", i, str[i]);
//             // p = list_position(p, i, 0);
//             while (str[i] && str[i] != ' ')
//             {
//                 if (str[i] == 34)
//                 {
//                     i++;
//                     while (str[i] && str[i] != 34)
//                     {
//                         if (str[i] == '*')
//                             star_in_quotes = 1;
//                         i++;
//                     }
//                 }
//                 else if (str[i] == 39)
//                 {
//                     i++;
//                     while (str[i] && str[i] != 39)
//                     {
//                         if (str[i] == '*')
//                             star_in_quotes = 1;
//                         i++;
//                     }
//                 }
//                 i++;
//             }
//             if (star_in_quotes == 1)
//             {
//                 star_in_quotes = 0;
//                 col--;
//             }
//         }
//         i++;
//     }
//     printf("col_star: %d\n", col);
//     // list_pos_print(p);
//     return (col);
// }

// void    check_wildcard(t_data *data)
// {
//     t_pipes *p;
//     int col;

//     col = 0;
//     p = data->pipes;
//     while (p != NULL)
//     {
//         col = search_col_star(p->cmd, p->pos_wildcard);
//         p = p->next;
//     }
    
// }