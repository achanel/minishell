/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:13 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 18:36:37 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MSL "🗿🗿"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"
# include <fcntl.h>

int		g_status;

typedef struct s_args
{
	int		ac;
	char	**av;
	char	*command;
}	t_args;

typedef struct s_fd
{
	int		fd_in;
	int		fd_out;
	int		fd_pipe_in;
	int		fd_pipe_out;
	char	*file_name;
	char	**str;
	int		i;
	int		j;
	int		k;
}	t_fd;

typedef struct s_envbase
{
	char				*key;
	char				*val;
	int					flag;
	struct s_envbase	*next;
}	t_envbase;

typedef struct s_two_env
{
	t_envbase	*origin;
	t_envbase	*sorted;
}	t_two_env;

//builtin
void		get_builtin(char **cmd, char **envp,
				t_two_env *env_lists, t_fd *fd);
void		do_pwd(void);
void		do_echo(char **av);
void		do_exit(char **cmd);
void		do_env(t_two_env *env, char **cmd);
void		do_unset(char **av, t_two_env **env);
void		do_cd(char **cmd, t_two_env *base);
void		do_export(char **cmd, t_two_env **env_list);
void		change_shlvl(t_two_env **env_lists);
//error_msg
void		error_msg(char *cmd, char *error, int status);
void		malloc_error(void *p);
void		path_error(char *path);
//utils_builtin.c
int			is_valid(int n);
int			unset_arg_check(char *str);
//utils_env.c
t_envbase	*add_new(char *key, char *val);
void		stack_add_back(t_envbase **stack, t_envbase *new);
t_envbase	*orig_env(char **env);
char		*search_in_env(t_envbase *base, char *s);
void		rewrite_pwd(t_envbase *base, char *pwd, char *s);
//utils_stack.c
int			is_in_stack(t_envbase *stack, char *key);
char		**sort_env(char **env);
char		*get_key(char *env_str);
char		*get_val(char *env_str);
//signal.c
void		exec_signal_catcher(void);
void		input_signal_catcher(void);
// paser
void		preparser(char **src, t_fd *fd);
char		**str_parse(char *str1, char **envp, t_fd *fd);
void		main_parcer(char **argv, char **env);
char		**args_split(char *str, char *c, t_fd *fd);
char		*get_path(char **envp, char *cmd);
char		*ft_perem(char *str, int *i, char **env);
void		ft_error(char *str);
void		main_redir(char **str, t_fd *fd);
char		*main_space(char **str, t_fd *fd);
//pipex
int			main_pipe(char *str, char **env, t_two_env *env_lists, t_fd *fd);
//utils_minishell
void		void_arg(int ac, char **av);
void		free_structs(t_two_env *base, t_fd *fd);
void		free_str(char **str);
void		*free_split(char **str);
//utils_parser.c
char		*str_null(char *str);
void		tmp_file(char *break_name);
char		*get_envp(char *perem, char **envp);
#endif
