/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:12:17 by achanel           #+#    #+#             */
/*   Updated: 2021/12/20 16:55:56 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	while(1)
	{
		str = readline("$lol_kek> ");
		if (str[0] != '\0')
			parser(str);
	}
	return (0);
}
