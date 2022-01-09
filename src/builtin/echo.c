/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:57 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 19:21:37 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	flag_parser(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[++i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
			count++;
	}
	if (count >= 1)
		return (count);
	else
		return (0);
}

void	do_echo(char **av)
{
	int	i;
	int	n;

	g_status = 0;
	i = 1;
	n = flag_parser(av);
	if (n > 0)
		i += n;
	while (av && av[i])
	{
		printf("%s", av[i]);
		i++;
		if (!av || !av[i])
			break ;
		printf(" ");
	}
	if (n == 0)
		printf("\n");
	g_status = 0;
}
