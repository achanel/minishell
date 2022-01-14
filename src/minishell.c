/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2022/01/14 16:43:10 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envbase(t_two_env **env_lists, char **env)
{
	char **sorted_env;

	*env_lists = malloc(sizeof(t_two_env));
	malloc_error(*env_lists);
	(*env_lists)->origin = orig_env(env);
	sorted_env = sort_env((*env_lists), env);
	(*env_lists)->sorted = orig_env(sorted_env);
}

static int	test_exec(char **cmd, char **env, int status)
{
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
		test_exec(cmd, env, status);
	waitpid(pid, &status, 0);
	g_status = WEXITSTATUS(status);
	input_signal_catcher();
	free_split(cmd);
}

static void	ft_eof(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("exit\n");
}

void fds_init(t_fd **fd)
{
	*fd = malloc(sizeof(t_fd));
	(*fd)->fd_in = 0;
	(*fd)->fd_out = 1;
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		**cmd;
	int i=0;
	pid_t pid0;
	t_two_env	*env_lists;
	t_fd	*fd;
	
	(void)ac;
	(void)av;
	cmd = NULL;
	init_envbase(&env_lists, env);
	fds_init(&fd);
	input_signal_catcher();
	hide_ctrl(env);
	str = NULL;
	printf("pid == %d\n", getpid());
	while(1)
	{	
		str = readline("🗿🗿> ");
		add_history(str);
		
		if (str == NULL)
		{
			// ft_eof();
			break ;
		}
		// else
		// {
			
			// pid0 = fork();
			// if (pid0 == 0){
				// if(main_pipe(str, env, env_lists, fd))
				cmd = str_parse(str, env, fd);
				if (cmd){
					
					get_builtin(cmd, env, env_lists, fd);
					free_split(cmd);	
				}
				// exit(0);
			// }
			// waitpid(pid0, 0, 0);
			// sleep(1);
		// }
		// while (env_lists->origin)
		// {
		// 	printf("%s == ", env_lists->origin->key);
		// 	// env_lists->origin = env_lists->origin->next;
		// 	printf("%s", env_lists->origin->val);
        // 	printf("\n");
        // 	env_lists->origin = env_lists->origin->next;
		// }
		// env_lists->origin = aaa;
		// if (str)
			free(str);
		// for(i = 0; cmd[i]; i++)
	}
	// write(1, "lol\n", 4);
	return (0);
}
