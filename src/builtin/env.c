/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:46:34 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 17:18:51 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_env(t_two_env *env, t_envbase *first)
{
	while(env->origin)
	{
		if (ft_strncmp(env->origin->key, "PATH", 4) == 0)
		{
			env->origin = first;
			break ;
		}
		env->origin = env->origin->next;
	}
}

void	do_env(t_two_env *env, char **cmd)
{
	t_envbase	*first;
	char		*str;

	g_status = 0;
	first = env->origin;
	check_env(env, first);
	if (!(env->origin) || cmd[1])
	{
		str = ft_strjoin("env: ", cmd[1]);
		error_msg(str, "No such file or directory\n", 1);
		env->origin = first;
		free(str);
		return ;
	}
	// printf("env1= %p\n", env->origin);
	// printf("env2= %p\n", env->origin->next);
	// printf("env3= %p\n\n", env->origin->next->next);
	while(env->origin)
	{
		// printf("env1= %p\n", env->origin);
		printf("%s", env->origin->key);
		printf("=");
		printf("%s", env->origin->val);
		printf("\n");
		env->origin = env->origin->next;
	}
	env->origin = first;
	return ;
}