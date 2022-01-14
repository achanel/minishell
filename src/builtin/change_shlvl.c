/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:36:48 by achanel           #+#    #+#             */
/*   Updated: 2022/01/13 13:41:41 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	level_error(int level)
{
	ft_putstr_fd("warning: shell level (", 2);
	ft_putnbr_fd(level, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}

static void	strdup_level(char **str, char *s)
{
	free(*str);
	*str = ft_strdup(s);
}

static void	shlvl_list_healper(char **val, int flag)
{
	int		level;
	char	*str;

	// printf("val2=%s\n", *val);
	level = ft_atoi(*val) + 1;
	// printf("level=%d\n", level);
	if (level == 1000)
		strdup_level(val, "\0");
	else if (level > 1000)
	{
		if (flag == 1)
			level_error(level);
		strdup_level(val, "1");
	}
	else
	{
		str = ft_itoa(level);
		// printf("str=%s\n", str);
		strdup_level(val, str);
		free(str);
	}
}

static void	shlvl_list(t_envbase *env, int flag)
{
	t_envbase	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strncmp(env->key, "SHLVL", 5) == 0)
		{
			if (env->val[0] == '\0')
			{
				strdup_level(&env->val, "1");
				break ;
			}
			else
			{
				// printf("here\n");
				shlvl_list_healper(&env->val, flag);
			}
			break ;
		}
		env = env->next;
	}
	env = tmp;
}

void	change_shlvl(t_two_env **env_lists)
{
	shlvl_list((*env_lists)->origin, 1);
	shlvl_list((*env_lists)->sorted, 0);
}
