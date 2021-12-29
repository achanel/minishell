/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:17:53 by achanel           #+#    #+#             */
/*   Updated: 2021/12/29 19:17:05 by achanel          ###   ########.fr       */
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

void	do_export(t_envbase *base, t_args *args)
{
	if ()
}