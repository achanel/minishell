/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:57 by achanel           #+#    #+#             */
/*   Updated: 2022/01/03 13:16:07 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	do_echo(char **av)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (ft_strncmp(av[1], "-n", 2) == 0)
	{
		n = 1;
		i = 2;
	}
	while(av && av[i])
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
