#include "philo.h"

void	error_exit(char *msg, int status)
{
	ft_putstr_fd(msg, 2);
	exit(status);
}
