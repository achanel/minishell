/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:12:22 by rhoke             #+#    #+#             */
/*   Updated: 2022/01/15 14:13:07 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)str;
	while (dst[i] != '\0')
		i++;
	while (dst[i] != (unsigned char)ch)
	{
		if (i == 0)
			return (0);
		i--;
	}
	return (&dst[i]);
}
