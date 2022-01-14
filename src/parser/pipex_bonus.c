/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:25 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/15 00:14:38 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *argv, char **env, t_two_env *env_lists, t_fd *fd)
{
	printf("argv == $%s$\n", argv);
	char	**cmd;

	cmd = NULL;
	if (argv){
		
		cmd = ft_split(argv, ' ');
	}
	write(2, "ded\n", 4);
	for(int i = 0; cmd[i]; i++){
		printf("cmd_pipex == %s$\n", cmd[i]);
	}
	if (cmd == NULL)
		cmd[0] = argv;
	get_builtin(cmd, env, env_lists, fd);
}

void	redir(char *cmd, char **envp, t_two_env *env_lists, t_fd *fd)
{
	pid_t	pid1;
	int		pipefd[2];
	int		buff_in;
	int		buff_out;

	
	
	printf("cmd == %s\n", cmd);
	pipe(pipefd);
	pid1 = fork();
	if (!pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid1, NULL, 0);
		// dup2(fd->fd_pipe_out, 1);
		// close(fd->fd_pipe_out);
		// close(fd->fd_pipe_in);
		// return ;
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		// if (fd->fd_pipe_in == 0)
		// 	exit (1);
		// else
		// {
			write(1, "SUKA\n", 5);
			exec(cmd, envp, env_lists, fd);
			
		// }
		// buff_in = dup(pipefd[0]);
		// dup2(fd->fd_pipe_in, 0);
		// exit(0);
	}

	return ;
}

int		main_pipe(char *str, char **env, t_two_env *env_lists, t_fd *fd)
{
	char **argv;
	int	i;

	int buff_fd_in;
	int buff_fd_out;
	
	i = 0;
	main_space(&str);
	main_redir(&str, fd);
	buff_fd_in = dup(0);
	buff_fd_out = dup(1);
	// printf("$%d$\n", str[0]);
	if(ft_strchr(" \t\0", str[0]) && ft_strlen(str) <= 1 && str[0] == 0)
		return (0);
	else{
		// write(1, "go home fag\n", 12);
		argv = args_split(str, "|");
	}
	for(int i = 0; argv[i]; i++){
		printf("cmd_pipex == %s$\n", argv[i]);
	}
	// printf("out == %d\nin == %d\n", fd->fd_out, fd->fd_in);
	// if (!argv)
	// 	return (1);
	// write(1, "lol\n", 4);
	// if (argv[1] == NULL)
	// 	return(1);
	main_parcer(argv, env);
	// write(2, "lol_pipe\n", 9);
	// dup2(0, fd->fd_pipe_in);
	// dup2(1, fd->fd_pipe_out);
	// for(i = 0; argv[i]; i++)
	// 	printf("argv_pipex == %s$\n", argv[i]);
	dup2(fd->fd_in, 1);
	dup2(fd->fd_out, 0);
	// redir(argv[0], env, env_lists, fd);
	while (argv[i]){
		printf("pipe str == %s\n", argv[i]);
		redir(argv[i++], env, env_lists, fd);
	}
	// exec(argv[i], env, env_lists, fd);
	
	dup2(buff_fd_in, 0);
	dup2(buff_fd_out, 1);
	return (0);
}
