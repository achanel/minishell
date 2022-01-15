/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:42:08 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 23:41:50 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	space_cut_helper(char *str, t_fd *fd, char *tmp)
{
	if (ft_strchr("\'\"", str[fd->i]))
	{
		tmp[fd->j++] = str[fd->i++];
		while (!ft_strchr("\'\"", str[fd->i]))
			tmp[fd->j++] = str[fd->i++];
		tmp[fd->j++] = str[fd->i++];
	}
	if (ft_strchr(" \t", str[fd->i]))
	{
		while (ft_strchr(" \t", str[++(fd->i)]))
			if (str[fd->i] == '\0')
				break ;
		fd->i--;
		tmp[fd->j++] = ' ';
	}
}

static char	*space_cut(char *str, t_fd *fd, char *tmp)
{
	char	*temp;

	fd->i = 0;
	fd->j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	malloc_error(tmp);
	while (str[fd->i])
	{
		if (ft_strchr(" \t\'\"", str[fd->i]))
			space_cut_helper(str, fd, tmp);
		if (!ft_strchr(" \t\'\"\0", str[fd->i]))
			tmp[fd->j++] = str[fd->i++];
		else
			fd->i++;
	}
	tmp[fd->j] = '\0';
	temp = tmp;
	free(tmp);
	return (temp);
}

void	main_space(char **str, t_fd *fd)
{
	char	*tmp;

	tmp = NULL;
	*str = ft_strdup(space_cut(*str, fd, tmp));
}
