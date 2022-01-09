/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 16:19:34 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
			error_msg(cmd[0], "command not found\n", 127);
}
