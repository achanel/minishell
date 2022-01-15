/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:47:08 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 01:55:46 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str2str(char *str, int *i, char c)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = malloc(ft_strlen(str) + 1);
	malloc_error(tmp);
	while (str[*i] == ' ' || str[*i] == '\t'
		|| str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
	while (str[*i] == c)
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t'
		|| str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		tmp[j++] = str[(*i)++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*redir_in(char *str, int *i, int flag, t_fd *fd)
{
	int		j;
	char	*file_name;
	char	*tmp;
	char	*tmp1;

	j = *i;
	tmp = ft_substr(str, 0, j);
	file_name = str2str(str, i, '<');
	tmp1 = ft_strdup(str + *i);
	str = ft_strjoin(tmp, tmp1);
	free(tmp1);
	free(tmp);
	tmp = str;
	*i = j + 1;
	if (flag)
	{
		tmp_file(file_name);
		fd->fd_in = open("temp_del", O_RDONLY, 0644);
	}
	else
		fd->fd_in = open(file_name, O_RDONLY, 0644);
	unlink("temp_del");
	free(file_name);
	return (tmp);
}

char	*redir_out(char *str, int *i, int flag, t_fd *fd)
{
	int		j;
	char	*file_name;
	char	*tmp;
	char	*tmp1;

	j = *i;
	tmp = ft_substr(str, 0, j);
	file_name = str2str(str, i, '>');
	tmp1 = ft_strdup(str + *i);
	str = ft_strjoin(tmp, tmp1);
	free(tmp1);
	free(tmp);
	tmp = str;
	*i = j;
	if (flag)
	{
		fd->fd_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		printf("fd_out_append == %d\n", fd->fd_out);
	}
	else
	{
		fd->fd_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		printf("fd_out == %d\n", fd->fd_out);
	}
	free(file_name);
	return (tmp);
}

static void	parcer(char **src, t_fd *fd)
{
	char	*str;
	int		i;

	str = *src;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<' && str[i + 2] != '<')
				str = redir_in(str, &i, 1, fd);
			else if (str[i + 1] != '<' && str[i] == '<')
				str = redir_in(str, &i, 0, fd);
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>' && str[i + 2] != '>')
				str = redir_out(str, &i, 1, fd);
			else if (str[i + 1] != '>' && str[i] == '>')
				str = redir_out(str, &i, 0, fd);
		}
	}
	*src = ft_strdup(str);
	free(str);
}

void	main_redir(char **str, t_fd *fd)
{
	fd->fd_in = 0;
	fd->fd_out = 1;
	parcer(str, fd);
}
