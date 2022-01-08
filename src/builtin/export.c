/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:17:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/03 14:05:08 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



static void	print_export(t_envbase *base)
{
	t_envbase	*tmp;

	tmp = base;
	while(tmp)
	{
		printf("declare -x%s=\"%s", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	do_export(char **cmd, t_two_env *env_list)
{
    g_status = 0;
    if (!cmd[1])
    {
        print_export(env_list->sorted);
        return ;
    }



}