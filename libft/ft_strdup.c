#include "libft.h"
//#include <stdio.h>

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		i;

	i = 0;
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
