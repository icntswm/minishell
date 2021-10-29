#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
#include "gnl/get_next_line.h"


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
    t_files *infile;
    t_files *outfile;
    t_pos   *pos_outred;
    t_pos   *pos_inred;
    struct s_pipes *next;
}               t_pipes;

typedef struct s_data
{
    char *error;
    char *line;
    int col_pipes;
    t_envp  *env;
    t_envp  *exp;
    t_pipes *pipes;
    t_pos *pos_pipe;
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
void	make_heredoc_files(t_data *data);

//signals
void	ctrl_c(int status);
void	ctrl_c_heredoc(int status);
void	ctrl_slash(int status);
void	ctrl_slash_heredoc(int status);

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
//-----handling dollar 2
char	*dollar_and_new_is_null(char *str, char *new, int i);
char	*search_envp_dollar(t_data *data, char *dollar);
int     compare_dollar_and_exp(char *exp, char *dollar);

//make cmd argv
void    make_cmd_argv(t_data *data);





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















void	ft_export(t_data *data);
void clean_export(t_envp *list);
#endif