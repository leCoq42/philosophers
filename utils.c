#include	"philo.h"

static void	ph_putchar_fd(char c, int fd);

int	ph_atoi(const char *str)
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

void	ph_putnbr_fd(int n, int fd)
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
		ph_putnbr_fd(n / 10, fd);
	ph_putchar_fd(n % 10 + '0', fd);
}

static void	ph_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return ;
}

void	ph_putstr_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
		if (write(fd, s++, 1) == -1)
			return ;
}

void	*ph_calloc(size_t count, uint_fast32_t size)
{
	void			*mem;
	unsigned char	*ptr;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ptr = (unsigned char *)mem;
	while (size-- > 0)
		*ptr++ = '\0';
	return (mem);
}
