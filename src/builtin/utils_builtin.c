/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:24:05 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 15:16:42 by achanel          ###   ########.fr       */
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

int	is_valid(int n)
{
	if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') || n == '_')
		return (0);
	return (1);
}

int	unset_arg_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && is_valid(str[i]))
		{
			path_error(str);
			return (0);
		}
		if (is_valid(str[i]) && ft_isdigit(str[i]))
		{
			path_error(str);
			return (0);
		}
	}
	return (1);
}
