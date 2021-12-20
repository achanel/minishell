/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dery_ru <dery_ru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:33:21 by dery_ru           #+#    #+#             */
/*   Updated: 2021/12/19 22:39:41 by dery_ru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_perem(char *str, int *i, char **env);

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (1);
}

char	*get_envp(char *perem, char **envp)
{
	char *str;
	char *tmp = NULL;
	int i = -1;
	str = ft_strjoin(perem, "=");
	
	while(envp[++i])
	{
		if (ft_strnstr(envp[i], str, ft_strlen(str)))
			tmp = envp[i] + ft_strlen(str);
		
			
	}
	return (tmp);
}

char	*ft_quote(char *str,int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[(*i)] == '$' && str[j] == '\"')
			str = ft_perem(str, i, env);
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
	printf("tmp == %s\n", tmp);
	return (tmp);
}

char	*ft_slesh(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	// write(1,"lol\n", 4);
	while (str[++(*i)])
		if (str[(*i)] == '\\')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	printf("tmp no slesh == %s\n", tmp);
	return (tmp);
}

char	*ft_perem(char *str, int *i, char **env)
{
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;
	
	j = *i;
	while (str[++(*i)])
		if (str[(*i)] == ' ' || str[(*i)] == '\"')
			break ;
	tmp = ft_substr(str, 0, j);
	if (!str[*i])
		return(tmp);
	printf("tmp == %s\n", tmp);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = get_envp(tmp2, env);
	printf("tmp2 == %s\n", tmp2);
	tmp3 = ft_strdup(str + *i);
	printf("tmp3 == %s\n", tmp3);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	return (tmp);
}

void	parser(char *str, char **env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\')
			str = ft_slesh(str, &i);
		if (str[i] == '\'' || str[i] == '\"')
			str = ft_quote(str, &i, env);
		if (str[i] == '$')
			str = ft_perem(str, &i, env);
		
	}
	printf("str == %s\n", str);
}

void	preparser(char *str, char **env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\'')
			j++;
	if ((j % 2))
		ft_error("Error: not closed \'\n"); // обработать не закрытую ковычку или ошибка
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\"')
			j++;
	if ((j % 2))
		ft_error("Error: not closed \"\n");
}	

int	main(int argc, char **argv, char **env)
{
	// '' "" \ $ ; | > >> <

	char *src = ft_strdup("lol\'$USER\'kek");
	if (argc == 2)
	{
		preparser(src, env);
		parser(src, env);	
	}
	// while(1);
}
