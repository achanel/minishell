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

void	do_unset(char *str)
{
	g_status = 0;
	if (!str)
		return ;
	while(str)
	{
		if (unset_arg_check(str))
		{
			//unset sorted env
			//unset env
		}
	}
}