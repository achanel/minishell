/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:25 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/15 21:10:48 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *argv, char **env, t_two_env *env_lists, t_fd *fd)
{
	char	**cmd;

	cmd = NULL;
	if (argv)
		cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		cmd[0] = argv;
	get_builtin(cmd, env, env_lists, fd);
}

void	redir(char *cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	pid_t	pid1;
	int		pipefd[2];

	pipe(pipefd);
	pid1 = fork();
	if (!pid1)
	{
		dup2(fd->fd_pipe_in, 0);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	exec(cmd, envp, env_lists, fd);
	waitpid(pid1, NULL, 0);
	return ;
}

int	main_pipe(char *str, char **env, t_two_env *env_lists, t_fd *fd)
{
	char	**argv;
	int		i;
	int		buff_fd_in;
	int		buff_fd_out;

	i = 0;
	main_space(&str);
	buff_fd_in = dup(0);
	buff_fd_out = dup(1);
	if (ft_strchr(" \t\0", str[0]) && ft_strlen(str) <= 1 && str[0] == 0)
		return (0);
	else
		argv = args_split(str, "|", fd);
	main_parcer(argv, env);
	dup2(fd->fd_pipe_in, 0);
	dup2(fd->fd_pipe_out, 1);
	main_redir(&argv[i], fd);
	exec(argv[i], env, env_lists, fd);
	dup2(buff_fd_in, 0);
	dup2(buff_fd_out, 1);
	return (0);
}
