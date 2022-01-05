/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:30 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/05 17:53:51 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char const *argv[], char **envp)
{
	char *str = ft_strdup("cat -e");
	int fd;
	char **str1 = args_split(str, " ");

	fd = open("test.c", O_RDONLY, 0644);
	dup2(fd, 0);
	close(fd);
	// write(0, str, ft_strlen(str));
	
	execve(get_path(envp, str1[0]), str1, envp);
	return 0;
}


//вырезать все последовательности \t и ' '
//  обработать в двойных кавычках делить изначально на пайпы возсожно можно будет сделать в 2 сплита