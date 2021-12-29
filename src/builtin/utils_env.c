/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:23:56 by achanel           #+#    #+#             */
/*   Updated: 2021/12/29 18:54:27 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_in_env(t_envbase *base, char *s)
{
	t_envbase	*tmp;

	tmp = base;
	while(tmp)
	{
		if (tmp->key == s)
			return(tmp->val);
		tmp = tmp->next;
	}
	return(NULL);
}

void	rewrite_pwd(t_envbase base, char *pwd, char *s)
{
	t_envbase	*path;

	path = base;
	while(path)
	{
		if (base->key == s)
			break ;
		path = path->next;
	}
	free(path->val);
	path->val = ft_strdup(s);
}