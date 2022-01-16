/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:47:08 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 19:07:12 by achanel          ###   ########.fr       */
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
	while (ft_isalnum(str[*i]) || str[*i] == '_'
		|| str[*i] == '/' || str[*i] == '.')
		tmp[j++] = str[(*i)++];
	tmp[j] = '\0';
	return (tmp);
}

char	*redir_in(char *str, int *i, int flag, t_fd *fd)
{
	int		j;
	char	*tmp;
	char	*tmp1;

	j = *i;
	tmp = ft_substr(str, 0, j);
	fd->file_name = str2str(str, i, '<');
	new_line_check(fd->file_name);
	tmp1 = tmp;
	free (tmp);
	str = ft_strjoin(tmp1, str + *i);
	free(tmp1);
	*i = j;
	if (flag)
	{
		tmp_file(fd->file_name);
		fd->fd_in = open("temp_del", O_RDONLY, 0644);
	}
	else
		fd->fd_in = open(fd->file_name, O_RDONLY, 0644);
	unlink("temp_del");
	return (str);
}

char	*redir_out(char *str, int *i, int flag, t_fd *fd)
{
	int		j;
	char	*tmp;
	char	*tmp1;

	j = *i;
	tmp = ft_substr(str, 0, j);
	fd->file_name = str2str(str, i, '>');
	new_line_check(fd->file_name);
	tmp1 = tmp;
	free (tmp);
	str = ft_strjoin(tmp1, str + *i);
	free(tmp1);
	*i = j;
	if (flag)
		fd->fd_out = open(fd->file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd->fd_out = open(fd->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (str);
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
	*src = str;
}

void	main_redir(char **str, t_fd *fd)
{
	fd->fd_in = 0;
	fd->fd_out = 1;
	parcer(str, fd);
}
