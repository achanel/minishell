/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:13 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 14:54:00 by achanel          ###   ########.fr       */
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
void	do_pwd(void);
void	do_echo(char **av);
void	do_echo_n(char **av);
void	do_exit(t_args *args);
void	do_env(t_two_env *env);
void	do_unset(char **av, t_two_env *env);

void	error_msg(char *cmd, char *error, int status);

void    del_env(t_envbase *base)
void    del_env_first(t_envbase *base);

#endif