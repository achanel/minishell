/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:33:21 by dery_ru           #+#    #+#             */
/*   Updated: 2022/01/15 19:37:29 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (1);
}

char	*get_envp(char *perem, char **envp)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (ft_strncmp(perem, "?", 1) == 0)
		return (ft_itoa(g_status));
	str = ft_strjoin(perem, "=");
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], str, ft_strlen(str)))
			tmp = envp[i] + ft_strlen(str);
	}
	if (tmp == NULL)
		tmp = "\0";
	free(str);
	return (tmp);
}

char	*ft_quote(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

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
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(str);
	free(tmp2);
	free(tmp3);
	return (tmp);
}

char	*ft_perem(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (str[(*i)] != '_' && (!ft_isalpha(str[(*i)])) && str[(*i)] != '?')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = get_envp(tmp2, env);
	tmp3 = ft_strdup(str + *i);
	if (tmp2[0] == '\0')
		(*i) = j;
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	return (tmp);
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

void	preparser(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!str)
		return ;
	while (str[++i])
		if (str[i] == '\'')
			j++;
	if ((j % 2))
		ft_error("Error: not closed \'\n");
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\"')
			j++;
	if ((j % 2))
		ft_error("Error: not closed \"\n");
}	

void	main_parcer(char **argv, char **env)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!argv || !argv[i])
			break ;
		preparser(argv[i]);
		parser(&argv[i], env);
		i++;
	}
}
