/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:18:55 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 14:45:14 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_list(t_envbase *base char *str)
{
	t_envbase *first;

	first = base;
	while(base)
	{
		if (ft_strncmp(first->val, str, ft_strlen(str)) == 0)
		{
			del_env_first(first);
			return ;
		}
		if (base->next && ft_strncmp(first->next->val, str, ft_strlen(str)) == 0)
		{
			del_env(base);
			break ;
		}
		first = first->next;
	}
	first = base;
}

static void	path_error(char *str)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	g_status = 1;
}

static int	is_valid(int n)
{
	if ((n >= 'A' && <= 'Z') || (n >= 'a' && <= 'z') || c == '_')
		return (0);
	return (1);
}

static int	unset_arg_check(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if (i == 0 && is_valid(str[i]))
		{
			unset_error(str);
			return (0);
		}
		if (is_valid(str[i] && !ft_isdigit(str[i]))
		{
			unset_error(str);
			return (0);
		}
	}
	return (1);
}

void	do_unset(char **av, t_two_env *env)
{
	int	i;

	i = 1;
	g_status = 0;
	if (!av[i])
		return ;
	while(av[i])
	{
		if (unset_arg_check(av[i]))
		{
			unset_list(env->origin, av[i]);
			unset_list(env->sortedm av[i]);
		}
		i++;
	}
}