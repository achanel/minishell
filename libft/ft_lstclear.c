/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:12:00 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 14:12:01 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*l;
	t_list	*last_save;

	l = *lst;
	while (l)
	{
		last_save = l->next;
		if (del)
			del(l->content);
		free(l);
		l = last_save;
	}
	*lst = NULL;
}
