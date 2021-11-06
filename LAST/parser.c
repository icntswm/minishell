#include "minishell.h"

void    parser(t_data *data)
{
    data->col_pipes = 0;
    data->error = NULL;
	data->pos_pipe = NULL;
	data->pipes = NULL;
    remove_spaces_in_line(&(*data)); // удаление пробелов в первоначальной строке
	search_pipe_position(&(*data)); // определение количества пайпов с учетом кавычек
	check_space_numfile(&(*data)); // проверка файла, название которого состоит из чисел
	if (data->error == NULL)
	{
		cut_pipe(&(*data));	//создание и заполнение листа по пайпам
		remove_spaces_pipe(&(*data)); // удаление пробелов по краям в строках, которые поделили по пайпам (cmd1 | cmd2 | cmd3)
		if (data->error == NULL)
		check_outredirect(&(*data)); // проверка ошибок > и >>
		if (data->error == NULL)
			check_inredirect(&(*data)); // проверка ошибок < и <<
		if (data->error == NULL)
		{
			heredoc_pipe(&(*data)); // проверка на наличие открытого пайпа (прим: ls -l |) и его обработка + клавиши
			check_heredoc_file(&(*data)); // тут проверяется наличие файлов heredoc_pipe и heredoc_error 
			if (data->error == NULL)
				check_outredirect(&(*data));
			if (data->error == NULL)
				check_inredirect(&(*data));
			if (data->error == NULL)
			{
				search_redirect_position(&(*data), '<'); // определение позиций инредиректов
				search_redirect_position(&(*data), '>'); // определение позиций аутредиректов
				if (data->error == NULL)
				{
					make_list(&(*data), '<'); // заполнение списка инфайлов
					make_list(&(*data), '>'); // заполнение списка аутфайлов
				}
			}
		}
	}
	if (data->error)
	{
		if ((ft_strncmp(data->error, "ctrl_c_pipe_heredoc", ft_strlen("ctrl_c_pipe_heredoc"))) != 0
			&& (ft_strncmp(data->error, "ctrl_c_redirect_heredoc", ft_strlen("ctrl_c_redirect_heredoc")))!= 0)
			printf("minishell: %s\n", data->error);
	}
	else
	{
		cutting_file(&(*data)); // вырезание файлов из строки cmd
		cutting_redirect(&(*data)); // вырезание редиректов < << <> >> > их строки cmd
		remove_spaces_cmd(&(*data)); // удаление пробелов в строке cmd
		// list_cmd_print(data->pipes); // печать
		remove_spaces_file(&(*data)); // удаление пробелов у имен файлов в списках infile и outfile
		make_cmd_argv(&(*data)); // создание двумерного массива cmd_argv, который заменит сплит в пайпексе
		quotes_and_dollar(&(*data)); // обработка кавычек и доллара в строке cmd и в файлах
		make_heredoc_files(&(*data)); // обработка <<, создание хердок файлов + клавиши
		check_heredoc_file(&(*data)); // тут проверяется наличие файлов heredoc_pipe и heredoc_error 
		// list_cmd_print(data->pipes);
		if (data->error == NULL)
		{
		}
		else
		{
			if (ft_strncmp(data->error, "warning: here-document delimited", ft_strlen("warning: here-document delimited")) == 0)
			{
				free(data->error);
				data->error = NULL;
			}
			else if ((ft_strncmp(data->error, "warning: here-document delimited", ft_strlen("warning: here-document delimited")) != 0)
				&& (ft_strncmp(data->error, "ctrl_c_redirect_heredoc", ft_strlen("ctrl_c_redirect_heredoc")) != 0) && data->error[0] != '\0')
			{
				if (data->error[0] != '\0')
					printf("minishell: %s\n", data->error);
			}
		}
	}
}

// "export "'"""' "'lol'" "'<<owefk $PATH'" "$PA'TH">feil0 $'P'A'T'H>"'f'ei'l4'" $USER $

//поправил ls -l >| wer и ls -l >|wer