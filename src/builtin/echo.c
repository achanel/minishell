/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:57 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 13:29:54 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	do_echo(char **av)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	// 		int p=0;
	// while (av[p])
	// 	{
	// 		printf("str to parse == %s\n", av[p]);
	// 		p++;
	// 	}
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
