/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:35:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 23:03:08 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*args_count(char *str, char *c, int *j)
{
	int		i;
	int		*count;

	count = malloc(sizeof(int) * 50);
	malloc_error(count);
	count[*j] = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\"')
				i++;
		}
		if (ft_strchr(c, str[i]))
			count[++(*j)] = i;
	}
	count[++(*j)] = ft_strlen(str);
	return (count);
}

void	comand_clean(char **str, char *c)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *str;
	i = 0;
	j = ft_strlen(tmp);
	while (ft_strchr(c, tmp[i]) || tmp[i] == '\t' || tmp[i] == ' ')
		i++;
	while (ft_strchr(c, tmp[j]) || tmp[j] == '\t' || tmp[j] == ' ')
		j--;
	j++;
	*str = ft_substr(tmp, i, j - i);
}

char	**args_split(char *str, char *c, t_fd *fd)
{
	char	**av;
	int		*ac;

	if (str[0] == '\0' || !str)
		return (NULL);
	comand_clean(&str, c);
	ac = args_count(str, c, &(fd->j));
	av = (char **)malloc(sizeof(char *) * fd->j + 1);
	malloc_error(av);
	fd->i = 0;
	fd->k = 0;
	while (fd->i < fd->j)
	{
		fd->i++;
		if (ac[fd->i] - ac[fd->i - 1] > 0)
		{
			av[fd->k] = ft_substr(str, ac[fd->i - 1],
					ac[fd->i] - ac[fd->i - 1]);
			comand_clean(&av[fd->k], c);
			fd->k++;
		}
	}
	av[fd->k] = NULL;
	free(ac);
	return (av);
}

char	**str_parse(char *str1, char **envp, t_fd *fd)
{
	char	**str2;

	str2 = NULL;
	main_space(&str1, fd);
	main_redir(&str1, fd);
	preparser(&str1, fd);
	if (!str1)
		return (NULL);
	if (ft_strchr(" \t\0", str1[0]) && ft_strlen(str1) <= 1)
		return (NULL);
	str2 = args_split(str1, " ", fd);
	main_parcer(str2, envp);
	return (str2);
}
