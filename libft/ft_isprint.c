#include "libft.h"

int	ft_isprint(int character)
{
	if (character >= 0x20 && character <= 0x7e)
		return (1);
	return (0);
}
