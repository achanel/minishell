/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:42:08 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 14:44:21 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*space_cut(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (ft_strchr(" \t\'\"", str[i]))
		{
			if (ft_strchr("\'\"", str[i]))
			{
				tmp[j++] = str[i++];
				while (1)
				{
					tmp[j++] = str[i++];
					if (ft_strchr("\'\"", str[i]))
						break ;
				}
				tmp[j++] = str[i++];
			}
			if (ft_strchr(" \t", str[i]))
			{
				while (ft_strchr(" \t", str[++i]))
					if (str[i] == '\0')
						break ;
				i--;
				tmp[j++] = ' ';
			}
		}
		if (!ft_strchr(" \t\'\"\0", str[i]))
			tmp[j++] = str[i++];
		else
			i++;
	}

	tmp[j] = '\0';
	return (tmp);
}

void	main_space(char **str)
{
	*str = ft_strdup(space_cut(*str));
}
