/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:25:16 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 14:11:35 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_null(char *str)
{
	g_status = 127;
	write(2, str, ft_strlen(str));
	return (NULL);
}

void	tmp_file(char *break_name)
{
	int		tmp;
	int		ret;
	char	buf[255];

	tmp = open("temp_del", O_RDWR | O_CREAT, 0644);
	if (tmp == -1)
		exit(EXIT_FAILURE);
	ret = 1;
	while (ret)
	{
		write(1, "> ", 2);
		ret = read(0, buf, 254);
		buf[ret] = '\0';
		if (ft_strncmp(ft_strjoin(break_name, "\n"), buf, ft_strlen(buf)) == 0)
			break ;
		write(tmp, buf, ft_strlen(buf));
	}
}

char	*get_envp(char *perem, char **envp)
{
	char	*str;
	char	*tmp;
	int		temp;
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
	free(perem);
	free(str);
	return (tmp);
}
