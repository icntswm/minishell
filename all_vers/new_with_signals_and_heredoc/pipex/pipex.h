// #ifndef PIPEX H
// # define PIPEX_H

// //built_in_cmds.c
// int		is_built_in(t_data *data, char **cmd, char ***envp);
// int		check_built_in(char *cmd);

// int		ft_cd(t_data *data, char **cmd, char ***envp);
// int		ft_echo(char **cmd);
// int		ft_env(t_data *data, char	**cmd);
// int		ft_exit(t_data *data, char **cmd);
// int		export_str(t_data *data, char *var, char *value, char ***envp);
// char	*find_var_name(char *str);
// int		print_export(t_data *data);
// int		ft_export(t_data *data, char **cmd, char ***envp);
// int		ft_pwd(char **cmd);
// int		ft_unset(t_data	*data, char **var, char ***envp);

// //funcs_for_pipe_fds.c
// int		**make_fds(int number_of_pipes);
// void	close_fds(int number_of_pipes, int **fd);
// void	free_fds(int number_of_pipes, int **fd);

// //get_exec_arguments.c
// void	free_array(char **arr);
// char	**get_exec_arguments(char *envp[], char *cmd_line);

// //get_fd.c
// int		get_out_fd(t_data *data, int i);
// int		get_in_fd(t_data *data, int i);

// //work_without_pipes.c
// int		work_without_pipes(t_data *data, char ***envp);

// //handle_multipipes.c
// int		handle_multipipes(t_data *data, char ***envp, int **fd, int *pid);

// //pipex.c
// int		pipex(t_data *data, char ***envp);

// #endif