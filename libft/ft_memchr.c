/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:12:19 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 14:12:20 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	cn;
	size_t			i;

	dst = (unsigned char *)src;
	cn = (unsigned char)c;
	i = 0;
	while (n-- > 0)
	{
		if (*dst == cn)
		{
			return (dst);
		}
		dst++;
	}
	return (0);
}
