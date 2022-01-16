/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 18:37:17 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envbase(t_two_env **env_lists, char **env)
{
	char	**sorted_env;

	*env_lists = malloc(sizeof(t_two_env));
	malloc_error(*env_lists);
	(*env_lists)->origin = orig_env(env);
	sorted_env = sort_env(env);
	(*env_lists)->sorted = orig_env(sorted_env);
}

static int	test_exec(char **cmd, char **env)
{
	int	status;

	status = execve(cmd[0], cmd, env);
	exit(status);
}

static void	hide_ctrl(char **env)
{
	char	**cmd;
	pid_t	pid;
	int		status;

	cmd = ft_calloc(3, sizeof(*cmd));
	malloc_error(cmd);
	cmd[0] = ft_strdup("/bin/stty");
	cmd[1] = ft_strdup("-echoctl");
	exec_signal_catcher();
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		test_exec(cmd, env);
	waitpid(pid, &status, 0);
	g_status = WEXITSTATUS(status);
	input_signal_catcher();
	free_split(cmd);
}

// static void	ft_eof(void)
// {
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	printf("exit\n");
// }

void	fds_init(t_fd **fd)
{
	*fd = malloc(sizeof(t_fd));
	malloc_error(*fd);
	(*fd)->str = malloc(sizeof(char *) * 50);
	(*fd)->fd_in = 0;
	(*fd)->fd_out = 1;
	(*fd)->fd_pipe_in = 0;
	(*fd)->fd_pipe_out = 1;
	(*fd)->file_name = NULL;
	(*fd)->i = 0;
	(*fd)->k = 0;
	(*fd)->j = 0;
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		**cmd;
	t_two_env	*env_lists;
	t_fd		*fd;

	void_arg(ac, av);
	cmd = NULL;
	init_envbase(&env_lists, env);
	fds_init(&fd);
	input_signal_catcher();
	hide_ctrl(env);
	str = NULL;
	while (1)
	{	
		str = readline("🗿🗿> ");
		add_history(str);
		if (str == NULL)
			break ;
		cmd = str_parse(str, env, fd);
		get_builtin(cmd, env, env_lists, fd);
		write(1, "kek\n", 4);
		free(str);
		free_split(cmd);
	}
	free_structs(env_lists, fd);
	return (0);
}
