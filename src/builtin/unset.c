/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:18:55 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 17:15:40 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_list(t_envbase *base, char *str)
{
	t_envbase	*first;

	first = base;
	while (base)
	{
		if (ft_strncmp(base->key, str, ft_strlen(str)) == 0)
		{
			base->flag = 0;
			return ;
		}
		if (base->next && ft_strncmp(base->next->key, str, ft_strlen(str)) == 0)
		{
			base->flag = 0;
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
