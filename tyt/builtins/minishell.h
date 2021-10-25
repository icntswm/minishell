#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "libft/libft.h"

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
    int redirect;
    struct s_pos *next;
}               t_pos;

typedef struct s_envp
{
    char    *var;
    struct s_envp *next;
}               t_envp;

typedef struct s_pipes
{
    
    char *cmd;
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
void	remove_spaces(t_data *data);
char	*ft_chartrim(char *s1, char set);
void    search_pipe_position(t_data *data);
t_pos 	*list_position(t_pos *list, int pos, int redirect);

//pipe cut
void	cut_pipe(t_data *data);
void	remove_spaces_pipe(t_data *data);
t_pipes	*list_pipe(t_pipes *list, char *str);

//checking redirects
void	check_inredirect(t_data *data);
void	check_outredirect(t_data *data);

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
void	heredoc_pipe(t_data *data);

//cutting file
void	cutting_file(t_data *data);
int     end_file(char *str, int start, int len);

//cutting redirect
void    cutting_redirect(t_data *data);
void	clean_redirect(t_pipes **list);

//builtind
void	ft_env(t_data *data);
t_envp  *make_envp(t_envp *list, char **envp);
t_envp  *list_envp(t_envp *list, char *str_env);
void	ft_export(t_data *data);

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
#endif