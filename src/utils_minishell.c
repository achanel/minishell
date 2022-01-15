/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:11:54 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 16:23:07 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	*free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[++i])
		free_str(&str[i]);
	free(str);
	return (NULL);
}
