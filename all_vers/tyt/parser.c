#include "minishell.h"

void    parser(t_data *data)
{
    data->col_pipes = 0;
    data->error = NULL;
	data->pos_pipe = NULL;
	data->pipes = NULL;
    remove_spaces_in_line(&(*data));	// удаление пробелов в первоначальной строке
    search_pipe_position(&(*data)); // определение количества пайпов с учетом кавычек
	check_space_numfile(&(*data)); // проверка файла, название которого состоит из чисел
	if (data->error == NULL)
	{
		cut_pipe(&(*data));	//создание и заполнение листа по пайпам
		remove_spaces_pipe(&(*data)); // удаление пробелов по краям в строках, которые поделили по пайпам (cmd1 | cmd2 | cmd3)
		check_inredirect(&(*data)); // проверка ошибок < и <<
		if (data->error == NULL)
			check_outredirect(&(*data)); // проверка ошибок > и >>
		if (data->error == NULL)
		{
			heredoc_pipe(&(*data)); // проверка на наличие открытого пайпа (прим: ls -l |)
			check_inredirect(&(*data));
			if (data->error == NULL)
				check_outredirect(&(*data));
			if (data->error == NULL)
			{
				search_redirect_position(&(*data), '<'); // определение позиций инредиректов
				search_redirect_position(&(*data), '>'); // определение позиций аутредиректов
				if (data->error == NULL)
				{
					make_list(&(*data), '<'); // заполнение списка инфайлов
					make_list(&(*data), '>'); // заполнение списка аутфайлов
					// list_cmd_print(data->pipes);
				}
			}
		}
	}
	if (data->error) // выводится ошибка и чистится память
		printf("\npipe: %d     error: %s\n", data->col_pipes, data->error);
	else
	{
		cutting_file(&(*data)); // вырезание файлов из строки cmd
		cutting_redirect(&(*data)); // вырезание редиректов < << <> >> > их строки cmd
		// list_cmd_print(data->pipes); // печать
	}
	remove_spaces_cmd(&(*data));
	remove_spaces_file(&(*data));
	make_cmd_argv(&(*data));
	quotes_and_dollar(&(*data));
	list_cmd_print(data->pipes);
	cleaning_pipe(data->pipes); 
	cleaning_position_pipe(data->pos_pipe);
	free(data->line);
	if (data->error)
	{
		printf("lol\n");
		free(data->error);
	}
}

// "export "'"""' "'lol'" "'<<owefk $PATH'" "$PA'TH">feil0 $'P'A'T'H>"'f'ei'l4'" $USER $

//поправил ls -l >| wer и ls -l >|wer