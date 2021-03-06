/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:17:53 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 18:19:04 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_envbase *base)
{
	t_envbase	*tmp;

	tmp = base;
	while (base)
	{
		if (base->flag == 0)
			base = base->next;
		if (base->val)
			printf("declare -x %s=\"%s\"\n", base->key, base->val);
		if (!base->val)
			printf("declare -x %s\n", base->key);
		base = base->next;
	}
	base = tmp;
}

static int	for_mid(t_two_env **env_list, t_envbase *new_elem)
{
	int	flag;

	flag = 0;
	while ((*env_list)->sorted->next)
	{
		if (ft_strncmp((*env_list)->sorted->key, new_elem->key,
				ft_strlen(new_elem->key)) < 0
			&& ft_strncmp((*env_list)->sorted->next->key, new_elem->key,
				ft_strlen(new_elem->key)) > 0)
		{
			flag = 1;
			new_elem->next = (*env_list)->sorted->next;
			(*env_list)->sorted->next = new_elem;
		}
		(*env_list)->sorted = (*env_list)->sorted->next;
	}
	if (flag)
		return (1);
	return (0);
}

static void	add_new_sorted(t_two_env **env_list, char *key, char *val)
{
	t_envbase	*new_elem;
	t_envbase	*first;
	int			flag;

	first = (*env_list)->sorted;
	flag = 0;
	new_elem = add_new(key, val);
	if (ft_strncmp((*env_list)->sorted->key, new_elem->key,
			ft_strlen(new_elem->key)) > 0)
	{
		new_elem->next = first;
		(*env_list)->sorted = new_elem;
		return ;
	}
	if (!for_mid(env_list, new_elem))
		(*env_list)->sorted->next = new_elem;
	(*env_list)->sorted = first;
}

static void	change_arg(t_two_env *env_list, char *arg)
{
	t_envbase	*tmp_sor;
	t_envbase	*tmp_ori;

	tmp_sor = env_list->sorted;
	tmp_ori = env_list->origin;
	while (env_list->origin)
	{
		if (ft_strncmp(env_list->origin->key, get_key(arg),
				ft_strlen(get_key(arg))) == 0)
			env_list->origin->val = get_val(arg);
		env_list->origin = env_list->origin->next;
	}
	while (env_list->sorted)
	{
		if (ft_strncmp(env_list->sorted->key, get_key(arg),
				ft_strlen(get_key(arg))) == 0)
			env_list->sorted->val = get_val(arg);
		env_list->sorted = env_list->sorted->next;
	}
	env_list->sorted = tmp_sor;
	env_list->origin = tmp_ori;
}

void	do_export(char **cmd, t_two_env **env_list)
{
	int	i;

	g_status = 0;
	if (!cmd[1])
	{
		print_export((*env_list)->sorted);
		return ;
	}
	i = 0;
	while (cmd[++i])
	{
		if (is_in_stack((*env_list)->sorted, get_key(cmd[i])))
			change_arg((*env_list), cmd[i]);
		else
			add_new_sorted(env_list, get_key(cmd[i]), get_val(cmd[i]));
	}
}
