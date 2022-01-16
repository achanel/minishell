/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:33:21 by dery_ru           #+#    #+#             */
/*   Updated: 2022/01/16 17:22:04 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_quote(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (str[++(*i)])
	{
		if (str[(*i)] == '$' && str[j] == '\"')
			str = ft_perem(str, i--, env);
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = str + *i + 1;
	tmp4 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp4);
	free(tmp2);
	tmp2 = tmp;
	return (tmp2);
}

char	*ft_perem(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (str[++(*i)])
		if (str[(*i)] != '_' && (!ft_isalpha(str[(*i)])) && str[(*i)] != '?')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = get_envp(tmp2, env);
	tmp3 = str + *i;
	if (tmp2[0] == '\0')
		(*i) = j;
	tmp4 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp4);
	tmp2 = tmp;
	return (tmp2);
}

void	parser(char **src, char **env)
{
	int		i;
	char	*str;

	str = *src;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str = ft_perem(str, &i, env);
		}
		if (str[i] == '\'' || str[i] == '\"')
			str = ft_quote(str, &i, env);
		i++;
	}
	*src = str;
}

void	preparser(char **src, t_fd *fd)
{
	char	*str;

	str = *src;
	fd->i = -1;
	fd->j = 0;
	while (str[++(fd->i)])
		if (str[fd->i] == '\'')
			fd->j++;
	if ((fd->j % 2))
		str = str_null("Error: not closed \'\n");
	if (!str)
	{
		*src = str;
		return ;
	}
	fd->i = -1;
	fd->j = 0;
	while (str[++(fd->i)])
		if (str[fd->i] == '\"')
			fd->j++;
	if ((fd->j % 2))
		str = str_null("Error: not closed \"\n");
	*src = str;
}	

void	main_parcer(char **argv, char **env)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!argv || !argv[i])
			break ;
		parser(&argv[i], env);
		i++;
	}
}
