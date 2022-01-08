/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:17:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/08 17:59:19 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_new_sorted(t_envbase *sorted, char *arg)
{
	t_envbase	*new_elem;
	t_envbase	*first;

	first = sorted;
	new_elem = add_new(arg, NULL);
	while(sorted)
	{
		if (ft_strncmp(sorted->key, new_elem->key, ft_strlen(new_elem->key)) < 0)
		{
			new_elem->next = sorted->next->next;
			sorted->next = new_elem;
		}
		sorted = sorted->next;
	}
	sorted = first;
}

static void	change_arg(t_two_env *env_list, char *arg)
{
	t_envbase	*tmp_sor;
	t_envbase	*tmp_ori;

	tmp_sor = env_list->sorted;
	tmp_ori = env_list->origin;
	while(env_list->origin)
	{
		if (ft_strncmp(env_list->origin->key, get_key(arg), ft_strlen(get_key(arg))) == 0)
			env_list->origin->val = get_val(arg);
		env_list->origin = env_list->origin->next;
	}
	while(env_list->sorted)
	{
		if (ft_strncmp(env_list->sorted->key, get_key(arg), ft_strlen(get_key(arg))) == 0)
		{
			env_list->sorted->val = get_val(arg);
		}
		env_list->sorted = env_list->sorted->next;
	}
	env_list->sorted = tmp_sor;
	env_list->origin = tmp_ori;
}

static void	print_export(t_envbase *base)
{
	t_envbase	*tmp;

	tmp = base;
	while(tmp)
	{
		printf("declare -x %s=\"%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	do_export(char **cmd, t_two_env *env_list)
{
	int	i;

    g_status = 0;
    if (!cmd[1])
    {
        print_export(env_list->sorted);
        return ;
    }
	i = 0;
	while (cmd[++i])
		if (get_key(cmd[i]) == cmd[i])
			add_new_sorted(env_list->sorted, cmd[i]);
	i = 0;
	while (cmd[++i])
		change_arg(env_list, cmd[i]);
}

//если нет аргумента неправильно печатается export