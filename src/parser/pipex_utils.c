/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:30 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/03 17:12:31 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_error(char *str)
// {
// 	write(2, str, ft_strlen(str));
// 	exit(EXIT_FAILURE);
// }

char	*get_path(char **envp, char *cmd)
{
	char	**path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			while (path[j])
			{
				if (access(ft_strjoin(ft_strjoin(path[j], "/"), cmd), 0) == 0)
					return (ft_strjoin(ft_strjoin(path[j], "/"), cmd));
				j++;
			}
		}
		i++;
	}
	return (0);
}
