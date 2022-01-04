/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:18:55 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 17:30:06 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    del_env(t_envbase **base)
{
    t_envbase   *tmp;

    if ((*base)->next->next)
        tmp = (*base)->next->next;
    free((*base)->next);
    if ((*base)->next->next)
        (*base)->next = tmp;
    else
        (*base)->next = NULL;
}

void	unset_list(t_two_env *base, char *str)
{
	t_envbase *first;
	t_envbase   *top;

	first = base->origin;
	while(base->origin)
	{

		if (ft_strncmp(base->origin->key, str, ft_strlen(str)) == 0)
		{
			
			top = base->origin->next;
			free(base->origin->key);
			free(base->origin->val);
    		free(base->origin);
			base->origin = NULL;
			base->origin = top;
			return ;
		}
		if (base->origin->next && ft_strncmp(base->origin->next->key, str, ft_strlen(str)) == 0)
		{
			del_env(&base->origin);
			break ;
		}
		base->origin = base->origin->next;
	}
	base->origin = first;
}

void	do_unset(char **av, t_two_env **env)
{
	int	i;

	i = 1;
	g_status = 0;
	if (!av[i])
		return ;
	while(av[i])
	{
		if (unset_arg_check(av[i]))
		{
			unset_list((*env), av[i]);
			// unset_list(env->sorted, av[i]);
		}
		i++;
	}
}
