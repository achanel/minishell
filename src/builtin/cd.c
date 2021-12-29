/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:35 by achanel           #+#    #+#             */
/*   Updated: 2021/12/29 18:55:57 by achanel          ###   ########.fr       */
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

static void	dir_to_path(t_envbase *base, char *path)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	rewrite_pwd(base, pwd, "OLDPWD");
	if (chdir(path))
	{
		path_error(path);
		return ;
	}
	pwd = getcwd(NULL, 0);
	rewrite_pwd(base, pwd, "PWD");
}

static void	dir_to_oldpwd(t_envbase *base, char *path)
{
	pritf("%s\n", path);
	dir_to_path(base, path);
}

static void	dir_to_home(t_envbase *base)
{
	char	*path;

	path = ft_strdup(search_in_env(base, "HOME"));
	if (!path)
	{
		error_msg("cd", "HOME not set", 1);
		free(path);
		return ;
	}
	dir_to_path(base, path);
	free(path);
}

void	do_cd(t_args *args, t_envbase *base)
{
	char		*cur_path;
	t_envbase	*path;

	path = base;
	while(path)
	{
		if (base->key == "PATH")
			break ;
		path = path->next;
	}
	if ((!path->key) || path->val == "~"))
	{
		dir_to_home(base);
		return ;
	}
	else if (path->val "-")
	{
		cur_path = ft_strdup(search_in_env(base, "OLDPWD"));
		if (!cur_path)
		{
			error_msg("cd", "OLDPWD not set", 1);
			return ;
		}
		dir_to_oldpwd(base, cur_path);
	}
	else
	{
		cur_path = ft_strdup(search_in_env(base, "PWD"));
		dir_to_path(base, path->val);
	}
	free(cur_path);
}
