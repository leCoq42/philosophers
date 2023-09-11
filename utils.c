#include	"philo.h"

static void	ft_putchar_fd(char c, int fd);

int	philo_atoi(const char *str)
{
	int	val;
	int	sign;

	val = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str > 47 && *str < 58)
		val = val * 10 + (*str++ - 48);
	return (val * sign);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == INT_MIN)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return ;
		return ;
	}
	else if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return ;
		n *= -1;
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}
