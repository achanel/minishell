/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2022/01/05 15:33:37 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_eof(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("exit\n");
}

void	init_envbase(t_two_env **env_lists, char **env)
{
	*env_lists = malloc(sizeof(t_two_env));
	malloc_error(*env_lists);
	(*env_lists)->origin = orig_env(env);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_two_env	*env_lists;
	char		**cmd;
	int i=0;

	(void)ac;
	(void)av;
	init_envbase(&env_lists, env);
	input_signal_catcher();
	while(1)
	{
		str = NULL;
		str = readline("🔥🔥🔥🔥🔥🔥> ");
		if (str == NULL)
		{
			ft_eof();
			break ;
		}
		else
			cmd = str_parse(str, env);
		get_builtin(cmd, env_lists, env);
		if (str)
			free(str);
	}
	return (0);
}
