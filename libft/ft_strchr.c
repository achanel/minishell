/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achanel <achanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:12:44 by achanel           #+#    #+#             */
/*   Updated: 2022/01/15 14:12:45 by achanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*s;

	s = (char *)str;
	while (*s != (unsigned char)ch)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return (s);
}

/*
int main()
{
    char src[10] = "";
    int ch = '6';
    printf("lib: %s\n", strchr(src, ch));
    printf("ft: %s\n", ft_strchr(src, ch));
}*/