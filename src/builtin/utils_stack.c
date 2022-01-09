/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:52:28 by achanel           #+#    #+#             */
/*   Updated: 2022/01/09 15:15:28 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_stack(t_envbase *stack, char *key)
{
	t_envbase	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**sort_env(t_two_env *env_list, char **env)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;

	count = 0;
	while (env[count])
		count++;
	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count)
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[j])) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
	return (env);
}

char	*get_key(char *env_str)
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	if (!env_str)
		return (NULL);
	while (env_str[++i])
	{
		if (env_str[i] == '=')
		{
			j = 0;
			while (env_str[j] != '=' && env_str[j])
				j++;
			key = malloc(sizeof(char) * j + 1);
			malloc_error(key);
			j = -1;
			while (env_str[++j] != '=')
				key[j] = env_str[j];
			key[j] = '\0';
			return (key);
		}
	}
	return (env_str);
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
	return (val);
}
