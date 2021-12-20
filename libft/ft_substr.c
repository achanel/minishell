#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	j;

	if (!s)
		return (0);
	if ((size_t)start >= ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc((len + 1) * sizeof(*sub));
	if (!sub)
		return (NULL);
	j = 0;
	while (j < len)
	{
		sub[j] = s[j + start];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
