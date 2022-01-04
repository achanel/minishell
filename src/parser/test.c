/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:30 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/04 19:18:32 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char const *argv[], char **envp)
{
	char *str = ft_strdup("cat -e test.c");
	char **str1 = args_split(str, " ");


	// write(0, str, ft_strlen(str));
	
	execve(get_path(envp, str1[0]), str1, envp);
	return 0;
}
