#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nn;

	nn = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nn = -nn;
	}
	if (nn >= 10)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putchar_fd(nn % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nn + '0', fd);
}
