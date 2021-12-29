/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:25 by rhoke             #+#    #+#             */
/*   Updated: 2021/08/25 15:52:55 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
	{
		ft_error(strerror(errno));
		exit(1);
	}
}

void	redir(char *cmd, char **envp, int filein)
{
	pid_t	pid1;
	int		pipefd[2];

	pipe(pipefd);
	pid1 = fork();
	if (pid1)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid1, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		if (filein == 0)
			exit(1);
		else
		{
			exec(cmd, envp);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;
	int	i;

	i = 3;
	if (argc >= 5)
	{
		filein = open(argv[1], O_RDONLY);
		fileout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 420);
		dup2(filein, 0);
		dup2(fileout, 1);
		redir(argv[2], envp, filein);
		while (i < argc - 2)
			redir(argv[i++], envp, 1);
		exec(argv[i], envp);
	}
	else
		ft_error("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
	return (0);
}
