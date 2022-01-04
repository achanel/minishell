/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 17:18:46 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_builtin(char **cmd, t_two_env *env_list)
{
	// printf("bul= %p\n", env_list->origin);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		do_pwd();
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		do_echo(cmd);
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		do_exit(cmd);
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		do_env(env_list, cmd);
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
		do_unset(cmd, &env_list);
	// if (ft_strncmp(args->command, "cd", 2) == 0)
	// 	do_cd(env_list->origin);
	// if (ft_strncmp(args->command, "export", 6) == 0)
	// 	do_export(args, env_list->origin);
	// execve(get_path(envp, str1[0]), str1, envp);
}
