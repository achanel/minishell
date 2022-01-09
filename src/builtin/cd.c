/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:35 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 18:30:48 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static t_envbase	*find_path(t_envbase *origin)
{
	t_envbase	*path;

	path = origin;
	while (path)
	{
		if (ft_strncmp(path->key, "PATH", 4) == 0)
			break ;
		path = path->next;
	}
	return (path);
}

void	do_cd(char **cmd, t_two_env *base)
{
	char		*cur_path;
	t_envbase	*path;

	g_status = 0;
	path = find_path(base->origin);
	if (!cmd[1] || ft_strncmp(cmd[1], "-", 1) == 0)
	{
		cur_path = search_in_env(base->origin, "OLDPWD");
		if (!cur_path)
		{
			error_msg("cd", "OLDPWD not set\n", 1);
			return ;
		}
		dir_to_oldpwd(base->origin, cur_path);
	}
	else if (!(path) || ft_strncmp(cmd[1], "~", 1) == 0)
	{
		dir_to_home(base->origin);
		return ;
	}
	else
		dir_to_path(base->origin, cmd[1]);
}
