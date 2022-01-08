/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:13 by achanel           #+#    #+#             */
/*   Updated: 2022/01/08 15:40:59 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MSL "minishell"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"
# include <fcntl.h> // хз надо не надо у меня была))

int		g_status;

typedef	struct s_args
{
	int		ac;
	char	**av;
	char	*command;
}	t_args;

typedef	struct s_envbase
{
	char				*key;
	char				*val;
	struct s_envbase	*next;
}	t_envbase;

typedef	struct s_two_env
{
	t_envbase	*origin;
	t_envbase	*sorted;
}	t_two_env;

//builtin
void	get_builtin(char **cmd, t_two_env *env_list, char **envp);
void	do_pwd(void);
void	do_echo(char **av);
void	do_exit(char **cmd);
void	do_env(t_two_env *env, char **cmd);
void	do_unset(char **av, t_two_env **env);
void	unset_list(t_two_env *base, char *str);
void	do_cd(char **cmd,t_two_env *base);
void	error_msg(char *cmd, char *error, int status);
void	malloc_error(void *p);
void	do_export(char **cmd, t_two_env *env_list);
//utils_builtin.c
int	is_valid(int n);
int	unset_arg_check(char *str);
//utils_env.c
t_envbase	*add_new(char *key, char *val);
void		stack_add_back(t_envbase **stack, t_envbase *new);
t_envbase	*orig_env(char **env);
char		*search_in_env(t_envbase *base, char *s);
void		rewrite_pwd(t_envbase *base, char *pwd, char *s);
//utils_stack.c
char	**sort_env(t_two_env *env_list, char **env);
char	*get_key(char *env_str);
char	*get_val(char *env_str);
//signal.c
void    exec_signal_catcher(void);
void    input_signal_catcher(void);
// paser
char 	**str_parse(char *str1, char **envp);
void	main_parcer(char **argv, char **env);
char	**args_split(char *str, char *c);
char	*get_path(char **envp, char *cmd);
char	*ft_perem(char *str, int *i, char **env);
void	ft_error(char *str);

#endif