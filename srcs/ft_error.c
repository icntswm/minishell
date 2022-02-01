#	include "minishell.h"

void	ft_error(t_data *data, char *error)
{
	if (ft_strncmp("newline", error, ft_strlen("newline")) == 0)
		data->error = ft_strdup("syntax error near unexpected token 'newline'");
	else if (ft_strncmp("pipe", error, ft_strlen("pipe")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '|'");
	else if (ft_strncmp("one_inred", error, ft_strlen("one_inred")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '<'");
	else if (ft_strncmp("two_inred", error, ft_strlen("two_inred")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '<<'");
	else if (ft_strncmp("three_inred", error, ft_strlen("three_inred")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '<<<'");
	else if (ft_strncmp("one_outred", error, ft_strlen("one_outred")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '>'");
	else if (ft_strncmp("two_outred", error, ft_strlen("two_outred")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '>>'");
	else if (ft_strncmp("red_pipe", error, ft_strlen("red_pipe")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '>|'");
	else if (ft_strncmp("inout_red", error, ft_strlen("inout_red")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '<>'");
	else if (ft_strncmp("double_pipe", error, ft_strlen("double_pipe")) == 0)
		data->error = ft_strdup("syntax error near unexpected token '||'");
	else if (ft_strncmp("quotes", error, ft_strlen("quotes")) == 0)
		data->error = ft_strdup("unclosed quotes found");
	g_question = 2;
}

void	error_malloc(int check)
{
	if (check == 1)
	{
		ft_putstr_fd("minishell: malloc: ", 2);
		ft_putstr_fd("memory allocation error\n", 2);
		g_question = 1;
		exit (1);
	}
}
