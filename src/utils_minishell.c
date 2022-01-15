/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:11:54 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 02:03:25 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_arg(int ac, char **av)
{
	(void)ac;
	(void)av;
}

static void	free_stack(t_envbase **stack)
{
	t_envbase	*tmp;

	while ((*stack)->next)
	{
		tmp = (*stack)->next;
		free((*stack)->key);
		free((*stack)->val);
		free (*stack);
		*stack = tmp;
	}
	free((*stack)->key);
	free((*stack)->val);
	free (*stack);
}

void	free_structs(t_two_env *base, t_fd *fd)
{
	free(fd->str);
	free(fd);
	free_stack(&base->origin);
	free_stack(&base->sorted);
	free(base);
}

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	*free_split(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free_str(&str[i]);
	free(str);
	return (NULL);
}
