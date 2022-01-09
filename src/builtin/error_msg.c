/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:20:26 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 15:31:37 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(char *cmd, char *error, int status)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	g_status = status;
}

void	malloc_error(void *p)
{
	if (!p)
	{
		ft_putstr_fd("Malloc ERROR\n", 2);
		exit(1);
	}
}

void	path_error(char *path)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
}
