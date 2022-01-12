/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2022/01/12 14:38:03 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		**cmd;
	int i=0;

	(void)ac;
	(void)av;
	cmd = NULL;
	input_signal_catcher();
	hide_ctrl(env);
	while(1)
	{
		str = NULL;
		str = readline("🗿🗿> ");
		add_history(str);
		if (str == NULL)
		{
			ft_eof();
			break ;
		}
		else
		{
			if(main_pipe(str, env))
				cmd = str_parse(str, env);	
		}
		// for(i = 0; cmd[i]; i++)
			
		if (cmd)
			get_builtin(cmd, env);
		free(str);
		free_split(cmd);
	}
	// write(1, "lol\n", 4);
	return (0);
}
