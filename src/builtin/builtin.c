/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 00:15:41 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void pidexecve(char **cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	pid_t pid0;

	pid0 = fork();
	if (pid0 == 0)
	{
		dup2(fd->fd_out, 1);
		dup2(fd->fd_in, 0);
		if (ft_strncmp(cmd[0], "minishell", 9) == 0 || ft_strncmp(cmd[0], "./minishell", 9) == 0)
			change_shlvl(&env_lists);
		if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
			error_msg(cmd[0], "command not found\n", 127);
		// if (fd->fd_in < 2)
		// 	close(fd->fd_in);
		// if (fd->fd_out < 2)
		// 	close(fd->fd_out);
		exit (0);
	}
	// else
	// {
	// 	waitpid(pid0, 0, 0);
	// 	// exit(0);
	// }
	waitpid(pid0, 0, 0);
	// if (fd->fd_in < 2)
	// 	close(fd->fd_in);
	// if (fd->fd_out < 2)
	// 	close(fd->fd_out);
}

void	get_builtin(char **cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	printf("\nlol4\n");

	
	int buff_fd_in;
	int buff_fd_out;

	
	// _stdin = dup(0);
	// _stdin = dup(1);
	// dup2(fd->fd_out, 1);
	write(2, "lol4\n", 5);
	printf("\tinfd %d\n\toutfd %d\n", fd->fd_in, fd->fd_out);
	buff_fd_in = dup(0);
	buff_fd_out = dup(1);
	// close(1);
	// close(0);
	// _stdin = dup(fd->fd_out);
	// close(fd->fd_out);
	// // STDIN_FILENO = dup(buff_fd_in);
	dup2(fd->fd_in, 0);
	dup2(fd->fd_out, 1);
	// dup2(fd->fd_in, fd->fd_pipe_in);
	// dup2(fd->fd_out, fd->fd_pipe_out);
	// _stdout = dup(fd->fd_in);
	// close(fd->fd_out);
	// dup2(1, fd->fd_out);
	// if (fd->fd_in > 2)
	// 	close(fd->fd_in);
	// if (fd->fd_out > 2)
	// 	close(fd->fd_out);
	// if (fd->fd_pipe_in > 2)
	// 	close(fd->fd_pipe_in);
	// if (fd->fd_pipe_out > 2)
	// 	close(fd->fd_pipe_out);
	// STDOUT_FILENO = dup(buff_fd_out);
	
	// dup2(fd->fd_in, 0);
	
	if (!cmd)
		return ;
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
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
	else{
		
		pidexecve(cmd, envp, env_lists, fd);
	}
		// if ((execve(get_path(envp, cmd[0]), cmd, envp)) == -1)
		// 	error_msg(cmd[0], "command not found\n", 127);
	// dup2(1, fd->fd_in);
	dup2(buff_fd_in, 0);
	dup2(buff_fd_out, 1);
	// buff_fd_in = dup(0);
	// buff_fd_out = dup(1);
}
