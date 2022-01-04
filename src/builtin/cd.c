/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:35 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 19:31:51 by achanel          ###   ########.fr       */
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
	ft_putstr_fd("\n", 2);
	g_status = 1;
}

static void	dir_to_path(t_envbase *base, char *path)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	rewrite_pwd(base, pwd, "OLDPWD");
	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
	{
		path_error(path);
		return ;
	}
	pwd = getcwd(NULL, 0);
	rewrite_pwd(base, pwd, "PWD");
}

static void	dir_to_oldpwd(t_envbase *base, char *path)
{
	printf("%s\n", path);
	dir_to_path(base, path);
}

static void	dir_to_home(t_envbase *base)
{
	char	*path;

	path = ft_strdup(search_in_env(base, "HOME"));
	if (!path)
	{
		error_msg("cd", "HOME not set\n", 1);
		free(path);
		return ;
	}
	dir_to_path(base, path);
	free(path);
}

void	do_cd(char **cmd, t_two_env *base)
{
	char		*cur_path;
	t_envbase	*path;

	path = base->origin;
	while(path)
	{
		if (ft_strncmp(path->key, "PATH", 4) == 0)
			break ;
		path = path->next;
	}
	if (!(path) || ft_strncmp(cmd[1], "~", 1) == 0)
	{
		dir_to_home(base->origin);
		return ;
	}
	else if (ft_strncmp(cmd[1], "-", 1) == 0)
	{
		cur_path = search_in_env(base->origin, "OLDPWD");
		if (!cur_path)
		{
			error_msg("cd", "OLDPWD not set\n", 1);
			return ;
		}
		dir_to_oldpwd(base->origin, cur_path);
	}
	else
		dir_to_path(base->origin, cmd[1]);
}
