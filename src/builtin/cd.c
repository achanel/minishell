/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:35 by achanel           #+#    #+#             */
/*   Updated: 2021/12/21 14:11:14 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	path_error(char *path)
{
	ft_putstr_fd(MSL, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	g_status = 1;
}

static void	dir_to_path(char *path)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	//записать -> OLDPWD = pwd
	if (chdir(path))
	{
		path_error(path);
		return ;
	}
	pwd = getcwd(NULL, 0);
	//записать -> PWD = pwd
}

static void	dir_to_oldpwd(char *path)
{
	pritf("%s\n", path);
	dir_to_path(path);
}

static void	dir_to_home(void)
{
	char	*path;

	path = HOME; //из env
	if (!path)
	{
		error_msg("cd", "HOME not set", 1);
		free(path);
		return ;
	}
	dir_to_path(path);
	free(path);
}

void	do_cd(char *path)
{
	char	*cur_path;

	if ((!path) || (ft_strncmp(path, "~", 1) == 0))
	{
		dir_to_home();
		return ;
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		cur_path = OLDPWD; //из env 
		if (!cur_path)
		{
			error_msg("cd", "OLDPWD not set", 1);
			return ;
		}
		dir_to_oldpwd(cur_path);
	}
	else
		dir_to_path(path);
}
