/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:52:28 by achanel           #+#    #+#             */
/*   Updated: 2022/01/04 19:36:47 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_list(t_envbase *first, t_envbase *tmp)
{
	t_envbase	*a;
	t_envbase	*b;
	t_envbase	*c;

	a = first;
	b = tmp->next;
	c = tmp->next->next;
	if (ft_strncmp(first->key, tmp->key, ft_strlen(tmp->key)) != 0)
	{
		while(ft_strncmp(a->next->key, tmp->key, ft_strlen(tmp->key)) != 0)
			a = a->next;
		a->next = b;
		tmp->next = c;
		b->next = tmp;
	}
	else
	{
		tmp->next = c;
		b->next = tmp;
		first->next = b;
	}
}

void	sort_env(t_envbase *sorted)
{
	t_envbase	*first;
	t_envbase	*tmp;
	int			i;

	first = sorted;
	while(sorted)
	{
		tmp = first;
		while (tmp)
		{
			if (ft_strncmp(tmp->key, tmp->next->key, ft_strlen(tmp->next->key)) > 0)
				swap_list(first, sorted);
			tmp = tmp->next;
		}
		sorted = sorted->next;
	}
	sorted = first;

}

char	*get_key(char *env_str)
{
	char	*key;
	int		i;

	i = 0;
	if (!env_str)
		return (NULL);
	while(env_str[i] != '=' && env_str[i])
		i++;
	key = malloc(sizeof(char) * i + 1);
	malloc_error(key);
	i = -1;
	while (env_str[++i] != '=')
		key[i] = env_str[i];
	key[i] = '\0';
	return(key);
}

char	*get_val(char *env_str)
{
	char	*val;
	int		i;

	val = NULL;
	i = 0;
	while (env_str[i])
	{
		if (env_str[i] == '=')
		{
			val = ft_strdup((char *)env_str + i + 1);
			break ;
		}
		else
			i++;
	}
	return(val);
}
