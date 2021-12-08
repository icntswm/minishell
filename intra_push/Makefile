NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -I includes/ -I libft/

LIBFT = -L libft/ -lft

HEADERS = includes/minishell.h\
			includes/get_next_line.h\
			libft/libft.h

PIPEX_SRC = ft_split.c\
			funcs_for_pipe_fds.c\
			get_exec_arguments.c\
			get_fd.c\
			handle_multipipes.c\
			pipex.c\
			work_without_pipes1.c\
			work_without_pipes2.c\
			dupping.c\
			check_built_in.c\
			built_in_get_fd.c

BUILTIN_SRC = built_in_cmds.c\
			ft_cd.c\
			ft_echo.c\
			ft_env.c\
			ft_exit.c\
			ft_export2.c\
			ft_export3.c\
			ft_export.c\
			ft_pwd.c\
			ft_unset.c

GNL_SRC = get_next_line.c\
			get_next_line_utils.c

MAIN_SRC = check_in_out_utils.c\
			check_inredirect.c\
			check_outredirect.c\
			check_space_numfile.c\
			cleaning.c\
			cutting_file.c\
			cutting_redirect.c\
			fill_redirectlist.c\
			ft_error.c\
			get_pid.c\
			handing_dollar1_1.c\
			handling_dollar1.c\
			handling_dollar2.c\
			handling_quotes.c\
			heredoc_pipe1.c\
			heredoc_pipe2.c\
			heredoc_redirect1.c\
			heredoc_redirect2.c\
			main.c\
			make_cmd_argv.c\
			make_env_and_exp_lists.c\
			parser.c\
			pipe_cut.c\
			quotes_and_dollar.c\
			remove_spaces_after.c\
			remove_spaces_before.c\
			search_pipe_position.c\
			search_redirect_position.c\
			signals.c\
			small_utils.c\
			handling_quotes_for_double_inred.c\

SRC = $(addprefix srcs/pipex/, $(PIPEX_SRC))\
	$(addprefix srcs/gnl/, $(GNL_SRC))\
	$(addprefix srcs/builtin/, $(BUILTIN_SRC))\
	$(addprefix srcs/, $(MAIN_SRC))\

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make fclean -C libft/
	rm -f $(OBJ)

fclean:
	make fclean -C libft/
	rm -f $(OBJ)
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
