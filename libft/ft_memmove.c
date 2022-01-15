/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:12:26 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 14:12:27 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr;
	char	*ptr2;

	if (!dst && !src)
		return (NULL);
	ptr = (char *)dst;
	ptr2 = (char *)src;
	if (ptr2 >= ptr)
		return (ft_memcpy(ptr, ptr2, len));
	while (len--)
		ptr[len] = ptr2[len];
	return (dst);
}
