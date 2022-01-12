/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dery_ru <dery_ru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/11 22:02:00 by dery_ru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void pidexecve(char **cmd, char **envp)
{
	pid_t pid0;

	pid0 = fork();
	if (pid0 == 0)
	{
		if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
			error_msg(cmd[0], "command not found\n", 127);
		exit(0);
	}
	else
	{
		// printf("lol");
		waitpid(-1, 0, 0);
	}
}

static void	init_envbase(t_two_env **env_lists, char **env)
{
	char **sorted_env;

	*env_lists = malloc(sizeof(t_two_env));
	malloc_error(*env_lists);
	(*env_lists)->origin = orig_env(env);
	sorted_env = sort_env((*env_lists), env);
	(*env_lists)->sorted = orig_env(sorted_env);
}

void	get_builtin(char **cmd, char **envp)
{
	t_two_env	*env_lists;
	
	// init_envbase(&env_lists, envp);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		do_pwd();
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)	
		do_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		do_exit(cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		do_env(env_lists, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		do_unset(cmd, &env_lists);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		do_cd(cmd, env_lists);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		do_export(cmd, env_lists);
	else
		pidexecve(cmd, envp);
		// if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
		// 	error_msg(cmd[0], "command not found\n", 127);
}
