/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:25 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/11 16:33:25 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	get_builtin(cmd, env);
}

void	redir(char *cmd, char **envp)
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
		exec(cmd, envp);
	}
}

int	main_pipe(char *str, char **env)
{
	char **argv;
	int	i;

	main_space(&str);
	// write(1, "lol\n", 4);
	main_redir(&str);
	argv = args_split(str, "|");
	if (argv[1] == NULL)
		return(1);
	main_parcer(argv, envp);
	while (argv[i])
		redir(argv[i++], env);
	exec(argv[i], env);
	return (0);
}
