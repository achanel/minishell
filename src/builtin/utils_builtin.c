/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:24:05 by achanel           #+#    #+#             */
/*   Updated: 2021/12/29 18:25:21 by achanel          ###   ########.fr       */
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
    first = tmp;
}

void    del_env_first(t_envbase *base)
{
    t_envbase   *first;
    t_envbase   *tmp;

    first = base;
    tmp = base->next;
    free(base->key);
    free(base->val);
    free(base);
    first = tmp;
}