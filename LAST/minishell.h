#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include "pipex/gnl/get_next_line.h"

//____NEW
# define AND_MODE 2
# define BOTH_MOD 12
//___

int question;

typedef struct s_files
{
    int mode;
    int pos;
    char *filename;
    struct s_files *next;
}               t_files;

typedef struct s_pos
{
    int pos;
    int red;
    struct s_pos *next;
}               t_pos;

typedef struct s_envp
{
    char    *var;
    struct s_envp *next;
}               t_envp;

typedef struct s_pipes
{
    int     num;
    char    *cmd;
    char    **cmd_argv;
    int     size_cmd_argv;
    t_files *infile;
    t_files *outfile;
    t_pos   *pos_outred;
    t_pos   *pos_inred;
    struct s_pipes *next;
}               t_pipes;

typedef struct s_data
{
    char    *error;
    char    *line;
    int     col_pipes;
    int     get_pid;
    t_envp  *env;
    t_envp  *exp;
    t_pipes *pipes;
    t_pos   *pos_pipe;
}               t_data;

int     main(int argc, char **argv, char **envp);
void	parser(t_data *data);
void    search_pipe_position(t_data *data);
t_pos 	*list_position(t_pos *list, int pos, int redirect);

// remove spaces before
void	remove_spaces_in_line(t_data *data);
char	*ft_chartrim(char *s1, char set);

//pipe cut
void	cut_pipe(t_data *data);
void	remove_spaces_pipe(t_data *data);
t_pipes *list_pipe(t_pipes *list, char *str, int num);

//checking redirects
void	check_inredirect(t_data *data);
int	help_inred(t_data *data, t_pipes *p, int i, int red);
void	check_outredirect(t_data *data);
int	help_outred(t_data *data, t_pipes *p, int i, int red);

//check space numfile
void    check_space_numfile(t_data *data);

//make outfile list
t_files	*list_file(t_files *list, char *str, int redirect);
t_files	*fill_list(t_data *data, t_pipes *pipes, char redrct);
void    make_list(t_data *data, char redrct);

//end_file
int	end_file(char *str, int start, int len);

//search position outfile
void	search_redirect_position(t_data *data, char redrct);

//heredoc pipe
//-----heredocpipe 1
void	heredoc_pipe(t_data *data);
//-----heredoc pipe 2
int	search_pipe_herdoc(t_data *data);
void	check_heredoc_file(t_data *data);

//heredoc redirect
//-----heredoc redirect 1
void	make_heredoc_files(t_data *data);
//-----heredoc redirect 2
int	check_str(int file, char *str, char *fname, int col);
void	error_heredoc_redrct_ctrl_d(char *name, int col);
int	counter_double_redrct(t_files *infile);

//signals
void	ctrl_c(int status);
void	ctrl_c_redirect_heredoc(int status);
void	ctrl_c_pipe_heredoc(int status);
void	ctrl_slash(int status);
void	ctrl_c_fork(int signal);

//cutting file
void	cutting_file(t_data *data);
int     end_file(char *str, int start, int len);

//cutting redirect
void    cutting_redirect(t_data *data);
void	clean_redirect(t_pipes **list);

//remove spaces after
void    remove_spaces_cmd(t_data *data);
void    remove_spaces_file(t_data *data);

//quotes and dollar
void    quotes_and_dollar(t_data *data);

//handling quotes
char	*handling_quotes(t_data *data, char *str);

//handling dollar
//-----handling dollar 1
char	*check_dollar(t_data *data, char *str, int lenght_str, int cmd_len);
char	*help_check_dollar(char *str, char *new);
int     dollar_change(char *str, char **new, int i, t_data *data);
int     help_dollar_change(char *str, char **new, int i, char *dollar);
char	*dollar_and_end_line(char *str, char *new, int i);
//-----handing dollar 1 1
int	dollar_question(int i, char *str, char **new);
int	dollar_pid(t_data *data, int i, char *str, char **new);
//-----handling dollar 2
char	*dollar_and_new_is_null(char *str, char *new, int i);
char	*search_envp_dollar(t_data *data, char *dollar);
int     compare_dollar_and_exp(char *exp, char *dollar);

//make cmd argv
void    make_cmd_argv(t_data *data);

//get pid
void	get_pid(t_data *data, char **envp);



void	make_heredoc_question_error(int num);







//error
void    ft_error(t_data *data, char *error);

//cleaning
void	cleaning_position_pipe(t_pos *list);
void	cleaning_pipe(t_pipes *list);

//print
void	list_pos_print(t_pos *list);
void	list_cmd_print(t_pipes *list);
int     skip_quotes(char *str, int quotes, int i);
void	envp_print(t_envp *list, int pointer);


void clean_export(t_envp *list);


//________NEW______!!!!!!!!!!!!!

//make_env_and_exp_lists.c
char	**make_new_envp(char **envp);
char	**refresh_envp(t_envp *env, char ***envp);

t_envp  *add_list_envp(t_envp *list, char *str);
t_envp	*make_envp(t_envp *list, char **envp);
void	init_data(t_data *data, char ***envp);

#endif

//________NEW______!!!!!!!!!!!!!

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_parser_info
{
	int	start;
	int	end;
	int	temp;
	int	quote;
}		t_parser_info;

//built_in_cmds.c
int		is_built_in(t_data *data, char **cmd, char ***envp);
int		check_built_in(char *cmd);

int		ft_cd(t_data *data, char **cmd, char ***envp);
int		ft_echo(char **cmd);
int		ft_env(t_data *data, char	**cmd);
int		ft_exit(t_data *data, char **cmd);
int		export_str(t_data *data, char *var, char *value, char ***envp);
char	*find_var_name(char *str);
int		print_export(t_data *data);
int		ft_export(t_data *data, char **cmd, char ***envp);
int		ft_pwd(char **cmd);
int		ft_unset(t_data	*data, char **var, char ***envp);

//funcs_for_pipe_fds.c
int		**make_fds(int number_of_pipes);
void	close_fds(int number_of_pipes, int **fd);
void	free_fds(int number_of_pipes, int **fd);

//ft_split.c
char	**ftt_split(char const *s, char c);
//parse_cmd_args.c
char	**free_args_and_return_null(int temp, char **strs);
int	    quote_case(char *s, char c);
int	    count_words(char *s, t_parser_info info);
char	**split_args(char *s);
//get_exec_arguments.c
void	free_array(char **arr);
char	**get_exec_arguments(char *envp[], char **cmd_args, t_data *data, int num);

//get_fd.c
int		get_out_fd(t_data *data, int i);
int		get_in_fd(t_data *data, int i);

//work_without_pipes1.c
int		work_without_pipes(t_data *data, char ***envp);
//work_without_pipes2.c
void	check_status_without_pipe(int status, char **cmd);
int	no_pipes_dupping(t_data *data);
void	help_get_path(t_data *data, int num, char **cmd_args);
//handle_here_doc.c
int	    make_here_doc_file(char	*limiter, char *name);
char	*make_filename(int i);

//handle_multipipes.c
int		handle_multipipes(t_data *data, char ***envp, int **fd, int *pid);

//pipex.c
int	    unlink_here_doc_files(t_data *data);
int     pipex(t_data *data, char ***envp);

#endif