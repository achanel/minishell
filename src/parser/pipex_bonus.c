/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:25 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/13 14:28:01 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(char *argv, char **env, t_two_env *env_lists)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	get_builtin(cmd, env, env_lists);
}

void	redir(char *cmd, char **envp, t_two_env *env_lists)
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
		write(1, "lol\n", 4);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		exec(cmd, envp, env_lists);
	}
}

int	main_pipe(char *str, char **env, t_two_env *env_lists)
{
	char **argv;
	int	i;

	main_space(&str);
	main_redir(&str);
	argv = args_split(str, "|");
	for(i = 0; argv[i]; i++)
		printf("argv_pipex == %s$\n", argv[i]);
	if (!argv)
		return (1);
	// write(1, "lol\n", 4);
	if (argv[1] == NULL)
		return(1);
	main_parcer(argv, env);
	while (argv[i])
		redir(argv[i++], env, env_lists);
	// exec(argv[i], env, env_lists);
	return (0);
}
