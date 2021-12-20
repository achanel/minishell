#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int		i;
	char	*dst;
	char	*sorc;

	dst = (char *)dest;
	sorc = (char *)src;
	i = 0;
	while (i < (int)n)
	{
		dst[i] = sorc[i];
		if (sorc[i] == (char)c || dst[i] == (char)c)
			return (dest + (++i));
		i++;
	}
	return (0);
}
