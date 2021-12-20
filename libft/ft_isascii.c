#include "libft.h"

int	ft_isascii(int character)
{
	if (character >= 0 && character <= 0x7f)
		return (1);
	return (0);
}
