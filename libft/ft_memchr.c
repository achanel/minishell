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
