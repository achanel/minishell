#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	char	*d;
	char	*s;

	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (char *)src;
	while (size--)
		*d++ = *s++;
	return (dst);
}
