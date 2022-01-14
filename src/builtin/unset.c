/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:18:55 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 15:18:40 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_first_env(t_envbase *base)
{
	t_envbase	*tmp;

	tmp = base->next;
	free(base->key);
	free(base->val);
	free(base);
	base = tmp;
}

static void	del_env(t_envbase *base)
{
	t_envbase	*tmp;

	if (base->next->next)
		tmp = base->next->next;
	free(base->next->key);
	free(base->next->val);
	free(base->next);
	if (base->next->next)
		base->next = tmp;
	else
		base->next = NULL;
}

static void	unset_list(t_envbase *base, char *str)
{
	t_envbase	*first;

	first = base;
	while (base)
	{
		if (ft_strncmp(base->key, str, ft_strlen(str)) == 0)
		{
			del_first_env(base);
			return ;
		}
		if (base->next && ft_strncmp(base->next->key, str, ft_strlen(str)) == 0)
		{
			del_env(base);
			break ;
		}
		base = base->next;
	}
	base = first;
}

void	do_unset(char **av, t_two_env **env)
{
	int	i;

	i = 1;
	g_status = 0;
	if (!av[i])
		return ;
	while (av[i])
	{
		if (unset_arg_check(av[i]))
		{
			unset_list((*env)->origin, av[i]);
			unset_list((*env)->sorted, av[i]);
		}
		i++;
	}
}
