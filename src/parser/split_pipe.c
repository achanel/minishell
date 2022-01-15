/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:35:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 19:54:30 by achanel          ###   ########.fr       */
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

char	**args_split(char *str, char *c)
{
	char	**av;
	int		j;
	int		i;
	int		*ac;
	int		k;

	j = 0;
	if (str[0] == '\0' || !str)
		return (NULL);
	comand_clean(&str, c);
	ac = args_count(str, c, &j);
	av = (char **)malloc(sizeof(char *) * j + 1);
	malloc_error(av);
	i = 0;
	k = 0;
	while (i < j)
	{
		i++;
		if (ac[i] - ac[i - 1] > 0)
		{
			av[k] = ft_substr(str, ac[i - 1], ac[i] - ac[i - 1]);
			comand_clean(&av[k], c);
			k++;
		}
	}
	av[k] = NULL;
	free(ac);
	return (av);
}

char	**str_parse(char *str1, char **envp, t_fd *fd)
{
	char	**str2;

	str2 = NULL;
	main_space(&str1);
	main_redir(&str1, fd);
	if (ft_strchr(" \t\0", str1[0]) && ft_strlen(str1) <= 1)
		return (NULL);
	str2 = args_split(str1, " ");
	// main_parcer(str2, envp);
	return (str2);
}
