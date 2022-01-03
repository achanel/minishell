/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:24:05 by achanel           #+#    #+#             */
/*   Updated: 2022/01/03 14:48:17 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    del_env(t_envbase *base)
{
    t_envbase   *tmp;

    if (base->next->next)
        tmp = base->next->next;
    free(base->next->key);
    free(base->next->val);
    free(base->next);
    if (base->next->next)
        base->next = tmp;
    else
        base->next = NULL;
}

void    del_env_first(t_envbase *base)
{
    t_envbase   *first;
    t_envbase   *tmp;

    first = base;
    tmp = base->next;
	printf("!!!!FFF!!!%s    %s\n", first->key, first->val);
	printf("!!!!TTT!!!%s    %s\n", tmp->key, tmp->val);
    free(base->key);
    free(base->val);
    free(base);
    base = tmp;
	printf("!!!!FFF!!!%s    %s\n", base->key, base->val);
}