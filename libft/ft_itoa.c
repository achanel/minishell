#include "libft.h"

static int	len_int(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while ((unsigned int)n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		i;
	int		len;

	i = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_int(n);
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (0);
	dst[len--] = '\0';
	if (n < 0)
	{
		dst[0] = '-';
		n = -n;
	}
	if (n == 0)
		dst[0] = '0';
	while (n > 0)
	{
		dst[len--] = n % 10 + '0';
		n /= 10;
	}
	return (dst);
}
