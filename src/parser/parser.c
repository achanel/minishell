/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:33:21 by dery_ru           #+#    #+#             */
/*   Updated: 2022/01/04 16:51:13 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_perem(char *str, int *i, char **env);

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (1);
}

// char	*get_envp(char *perem, char **envp, int *j)
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
	if (tmp == NULL)
		tmp = "\0";
	// *j += ft_strlen(str) - 1 - ft_strlen(tmp); 
	// printf("str in env == %s\n", tmp);
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
			str = ft_perem(str, i--, env);
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	// printf("tmp in \" == %s\n", tmp);
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
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;
	
	j = *i;
	while (str[++(*i)])
		if (str[(*i)] != '_' || (!ft_isalpha(str[(*i)])))
			break ;
	// printf("i_ out == %d\n", *i);
	
	tmp = ft_substr(str, 0, j);
	if (!str[*i])
		return(tmp);
	// printf("tmp == %s\n", tmp);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	// tmp2 = get_envp(tmp2, env, i); // убрать сдвиг по i когда переменная не найдена
	tmp2 = get_envp(tmp2, env); // убрать сдвиг по i когда переменная не найдена
	tmp3 = ft_strdup(str + *i);
	// printf(" !!!tmp3 == %s\n", tmp3);
	if (tmp2[0] == '\0'){
		(*i) = j;
	}
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	// printf("tmp_out == %s\n", tmp);
	return (tmp);
}

void	parser(char **src, char **env)
{
	int	i;
	char *str;

	str = *src;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'){
			str = ft_perem(str, &i, env);
			// printf( " now i == %d == %c\n", i, str[i]);
		}
		if (str[i] == '\'' || str[i] == '\"')
			str = ft_quote(str, &i, env);
		i++;
	}
	*src = str;
	// printf("str == %s\n", str);
}

void	preparser(char *str, char **env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str)
		return;
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

void	main_parcer(char **argv, char **env)
{
	// '' "" $ | > >> <

	int i = 0;
	while(argv[i])
	{
		// write(1, "lol\n", 4);
		// printf("%s\n", argv[i]);
		preparser(argv[i], env);
		parser(&argv[i], env);
		i++;
	}
	// i = 0;
	// while(argv[i])
	// {
	// 	printf("str%d == %s\n", i, argv[i]);
	// 	i++;
	// }
}
