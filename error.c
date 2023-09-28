#include "philo.h"
#include <stdint.h>

/* void	error_exit(char *msg, int status) */
/* { */
/* 	ph_putstr_fd(msg, 2); */
/* 	exit(status); */
/* } */

int	input_check(int argc, char **argv)
{
	if (ph_atoi(argv[1]) < 2 || (unsigned long)ph_atoi(argv[1]) > UINT_FAST8_MAX)
		return (1);
	if (ph_atoi(argv[2]) < 120 || (unsigned long)ph_atoi(argv[2]) > UINT_FAST32_MAX)
		return (1);
	if (ph_atoi(argv[3]) <  60 || (unsigned long)ph_atoi(argv[3]) > UINT_FAST32_MAX)
		return (1);
	if (ph_atoi(argv[4]) < 60 || (unsigned long)ph_atoi(argv[4]) > UINT_FAST32_MAX)
		return (1);
	if (argc == 6)
	{
		if (ph_atoi(argv[5]) < 1 || (unsigned long)ph_atoi(argv[5]) > UINT_FAST32_MAX)
			return (1);
	}
	return (0);
}
