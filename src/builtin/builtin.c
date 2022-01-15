/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 22:18:25 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pidexecve(char **cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	pid_t	pid0;

	pid0 = fork();
	exec_signal_catcher();
	if (pid0 == 0)
	{
		dup2(fd->fd_out, 1);
		dup2(fd->fd_in, 0);
		if (ft_strncmp(cmd[0], "minishell", 9) == 0
			|| ft_strncmp(cmd[0], "./minishell", 9) == 0)
			change_shlvl(&env_lists);
		if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
			error_msg(cmd[0], "command not found\n", 127);
		exit (0);
	}
	waitpid(pid0, 0, 0);
}

static void	my_builtin(char **cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	if (!cmd)
		return ;
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
		do_export(cmd, &env_lists);
	else
		pidexecve(cmd, envp, env_lists, fd);
}

void	get_builtin(char **cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	int	buff_fd_in;
	int	buff_fd_out;

	buff_fd_in = dup(0);
	buff_fd_out = dup(1);
	dup2(fd->fd_in, 0);
	dup2(fd->fd_out, 1);
	if (fd->fd_in > 2)
		close(fd->fd_in);
	if (fd->fd_out > 2)
		close(fd->fd_out);
	my_builtin(cmd, envp, env_lists, fd);
	dup2(buff_fd_out, 1);
	dup2(buff_fd_in, 0);
}
