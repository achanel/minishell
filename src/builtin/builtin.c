/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/11 15:18:51 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void pidexecve(char **cmd, char **envp)
{
	pid_t pid0;

	pid0 = fork();
	if (pid0)
	{
		waitpid(pid0, NULL, 0);
	}
	else
	{
		if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
				error_msg(cmd[0], "command not found\n", 127);
	}
}

void	get_builtin(char **cmd, t_two_env *env_list, char **envp)
{
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		do_pwd();
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		do_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		do_exit(cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		do_env(env_list, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		do_unset(cmd, &env_list);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		do_cd(cmd, env_list);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		do_export(cmd, env_list);
	else
		pidexecve(cmd, envp);
		// if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
		// 	error_msg(cmd[0], "command not found\n", 127);
}
