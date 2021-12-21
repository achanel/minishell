/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:12 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 11:24:38 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_builtin(char *command, int ac, char **av, char **env)
{
	if (ft_strncmp(command, "pwd", 3) == 0)
		do_pwd();
	if (ft_strncmp(command, "echo", 4) == 0)
		do_echo(av);
	if (ft_strncmp(command, "echo -n", 7) == 0)
		do_echo_n(av);
	if (ft_strncmp(command, "exit", 4) == 0)
		do_exit(ac, av);
	if (ft_strncmp(command, "cd", 2) == 0)
		do_cd();
	if (ft_strncmp(command, "export", 6) == 0)
		do_export();
	if (ft_strncmp(command, "unset", 5) == 0)
		do_unset();
	if (ft_strncmp(command, "env", 3) == 0)
		do_env();
}