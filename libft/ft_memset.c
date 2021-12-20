#include "libft.h"

void	*ft_memset(void *src, int c, size_t len)
{
	char	*p;

	p = (char *)src;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (src);
}
