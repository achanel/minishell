/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:12:46 by achanel           #+#    #+#             */
/*   Updated: 2022/01/16 01:09:18 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dst = (char *)malloc((ft_strlen(str) + 1) * sizeof(*str));
	if (!dst)
		return (0);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
