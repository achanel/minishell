/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:16:57 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 11:20:08 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	do_echo(char **av)
{
	int	i;

	i = 0;
	while(av && av[++i])
		printf("%s", av[i]);
	printf("\n");
	g_status = 0;
}

void	do_echo_n(char **av)
{
	int	i;

	i = 0;
	while(av && av[++i])
		printf("%s", av[i]);
	g_status = 0;
}
