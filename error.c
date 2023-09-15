#include "philo.h"

void	error_exit(char *msg, int status)
{
	ph_putstr_fd(msg, 2);
	exit(status);
}
