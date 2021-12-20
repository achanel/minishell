/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2021/12/20 15:59:47 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	get_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		do_echo();
	if (ft_strncmp(command, "echo -n", 7) == 0)
		do_echo_n();
	if (ft_strncmp(command, "cd", 2) == 0)
		do_cd();
	if (ft_strncmp(command, "pwd", 3) == 0)
		do_pwd();
	if (ft_strncmp(command, "export", 6) == 0)
		do_export();
	if (ft_strncmp(command, "unset", 5) == 0)
		do_unset();
	if (ft_strncmp(command, "env", 3) == 0)
		do_env();
	if (ft_strncmp(command, "exit", 4) == 0)
		do_exit();		
}