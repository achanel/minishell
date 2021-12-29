/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:46:34 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 14:17:26 by achanel          ###   ########.fr       */
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

void	do_env(t_two_env *env)
{
	t_envbase	*first;

	g_status = 0;
	first = env->origin;
	check_env(env, first);
	if (!(env->origin))
	{
		error_msg(env, ": No such file or directory\n", 1);
		env->origin = first;
		return ;
	}
	while(env->origin)
	{
		printf("%s", env->origin->key);
		printf("=");
		printf("%s", env->origin->val);
		printf("\n");
		env->origin = env->origin->next;
	}
	env->origin = first;
	return ;
}