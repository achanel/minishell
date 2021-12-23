/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoke <rhoke@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:51:14 by rhoke             #+#    #+#             */
/*   Updated: 2021/08/25 15:52:54 by rhoke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	size_t	little_len;
	size_t	i;
	size_t	j;

	b = (char *)big;
	little_len = ft_strlen(little);
	if (*little == '\0' || little == NULL)
		return (b);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && little[j] == b[i + j])
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}
