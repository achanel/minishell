/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:25:16 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 19:06:09 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_null(char *str)
{
	g_status = 127;
	write(2, str, ft_strlen(str));
	return (NULL);
}

static void	new_line_error(void)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": syntax error\n", 2);
	g_status = 258;
}

void	new_line_check(char *file_name)
{
	if ((ft_strncmp(file_name, " ", 0) == 0)
		|| (ft_strncmp(file_name, "\0", 0) == 0))
		new_line_error();
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
