/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:59:55 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 13:36:24 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_pwd(void)
{
	char	*cwd;

	g_status = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putstr_fd(strerror(errno), 2);
	else
		printf("%s\n", cwd);
	free(cwd);
}
