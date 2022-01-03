/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:23:56 by achanel           #+#    #+#             */
/*   Updated: 2022/01/03 14:07:31 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envbase	*add_new(char *key, char *val)
{
	t_envbase	*stack;

	stack = malloc(sizeof(t_envbase));
	//malloc_error;
	stack->key = key;
	stack->val = val;
	stack->next = NULL;
	return (stack);
}

void	stack_add_back(t_envbase **stack, t_envbase *new)
{
	t_envbase	*tmp;

	if (!*stack)
	{
		*stack = new;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	new->next = NULL;
	tmp->next = new;
}

t_envbase	*orig_env(char **env)
{
	t_envbase	*new_envbase;
	int			i;

	new_envbase = NULL;
	i = -1;
	while(env[++i])
		stack_add_back(&new_envbase, add_new(get_key(env[i]), get_val(env[i])));
	return(new_envbase);
}

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

void	rewrite_pwd(t_envbase *base, char *pwd, char *s)
{
	t_envbase	*path;

	path = base;
	pwd = 0; //////
	while(path)
	{
		if (base->key == s)
			break ;
		path = path->next;
	}
	free(path->val);
	path->val = ft_strdup(s);
}
