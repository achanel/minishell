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
