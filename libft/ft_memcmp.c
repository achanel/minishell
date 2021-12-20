#include "libft.h"

int	ft_memcmp(const void *src1, const void *src2, size_t n)
{
	unsigned const char	*s1;
	unsigned const char	*s2;

	s1 = (unsigned const char *)src1;
	s2 = (unsigned const char *)src2;
	while (n)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
