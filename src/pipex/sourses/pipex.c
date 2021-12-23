/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:35:41 by rhoke             #+#    #+#             */
/*   Updated: 2021/08/25 15:53:02 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_child(int *fd, char **argv, char **envp)
{
	int		in;
	char	**cmd;

	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error(strerror(errno));
	in = open(argv[1], O_RDONLY);
	if (in == -1)
	{
		ft_error(strerror(errno));
		exit (1);
	}
	if (dup2(in, 0) == -1)
		ft_error(strerror(errno));
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(argv[2], ' ');
	if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
	{
		ft_error(strerror(errno));
		exit(1);
	}
}

void	ft_father(int *fd, char **argv, char **envp)
{
	int		out;
	char	**cmd;
	char	*path;

	out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, S_IREAD | S_IWRITE);
	wait(0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error(strerror(errno));
	if (dup2(out, 1) == -1)
		ft_error(strerror(errno));
	close(fd[1]);
	close(fd[0]);
	cmd = ft_split(argv[3], ' ');
	path = get_path(envp, cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		ft_error(strerror(errno));
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	int		fd[2];

	if (argc != 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	if (pipe(fd) == -1)
		ft_error(strerror(errno));
	pid1 = fork();
	if (pid1 < 0)
		ft_error(strerror(errno));
	if (pid1 == 0)
		ft_child(fd, argv, envp);
	else
		ft_father(fd, argv, envp);
	return (0);
}
