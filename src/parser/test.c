/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dery_ru <dery_ru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:30 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/07 17:26:51 by dery_ru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (strncmp(ft_strjoin(break_name, "\n"), buf, ft_strlen(buf)) == 0)
			break ;
		write(tmp, buf, ft_strlen(buf));
	}
	dup2(tmp, 0);
	close(tmp);
}

int main(int argc, char const *argv[], char **envp)
{
	char *str = ft_strdup("cat -e");
	int fd;
	char **str1 = args_split(str, " ");

	// fd = open("test.c", O_RDONLY, 0644);
	tmp_file("lol");
	// dup2(fd, 0);
	// close(fd);
	// write(0, str, ft_strlen(str));
	
	execve(get_path(envp, str1[0]), str1, envp);
	return 0;
}


//вырезать все последовательности \t и ' '
//  обработать в двойных кавычках делить изначально на пайпы возсожно можно будет сделать в 2 сплита