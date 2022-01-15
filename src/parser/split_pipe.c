/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:35:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 00:51:59 by rhoke            ###   ########.fr       */
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

char	*comand_clean(char *str, char *c)
{
	int		i;
	int		j;
	char	*tmp;
	char	*temp;

	tmp = str;
	i = 0;
	j = ft_strlen(tmp);
	while (ft_strchr(c, tmp[i]) || tmp[i] == '\t' || tmp[i] == ' ')
		i++;
	while (ft_strchr(c, tmp[j]) || tmp[j] == '\t' || tmp[j] == ' ')
		j--;
	j++;
	str = ft_substr(tmp, i, j - i);
	// str = temp;
	// free(temp);
	return (str);
}

char	**args_split(char *str, char *c, t_fd *fd)
{
	char	**av;
	char	*temp;
	int		*ac;

	if (str[0] == '\0' || !str)
		return (NULL);
	str = comand_clean(str, c);
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
			temp = ft_substr(str, ac[fd->i - 1],
					ac[fd->i] - ac[fd->i - 1]);
			av[fd->k] = temp;
			av[fd->k] = comand_clean(av[fd->k], c);
			fd->k++;
			free(temp);
		}
	}
	av[fd->k] = NULL;
	free(ac);
	free (str);
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
