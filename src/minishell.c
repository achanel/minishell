/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2022/01/03 15:23:20 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envbase(t_two_env **env_lists, char **env)
{
	*env_lists = malloc(sizeof(t_two_env));
	//malloc_error;
	(*env_lists)->origin = orig_env(env);
}

static void	pre_builtin(char *str, t_two_env *env_list)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	get_builtin(cmd, env_list);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_two_env	*env_lists;
	char		**cmd;

	(void)ac;
	(void)av;
	while(1)
	{
		str = readline("🔥> ");
		init_envbase(&env_lists, env);
		// input_signal_catcher();
		// if (str[0] != '\0')
		// 	cmd = parser(str, env);
		// get_builtin(cmd, env_list);
		pre_builtin(str, env_lists);
	}
	return (0);
}
