/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 14:12:36 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_builtin(t_args *args, t_two_env *env)
{
	if (ft_strncmp(args->command, "pwd", 3) == 0)
		do_pwd();
	if (ft_strncmp(args->command, "echo", 4) == 0)
		do_echo(args->av);
	if (ft_strncmp(args->command, "echo -n", 7) == 0)
		do_echo_n(args->av);
	if (ft_strncmp(args->command, "exit", 4) == 0)
		do_exit(args);
	if (ft_strncmp(base->command, "env", 3) == 0)
		do_env(env);
	if (ft_strncmp(base->command, "export", 6) == 0)
		do_export(base);
	if (ft_strncmp(base->command, "unset", 5) == 0)
		do_unset(base);
	if (ft_strncmp(args->command, "cd", 2) == 0)
		do_cd(base);
}