#include "philo.h"
#include <stdint.h>

int	input_check(int argc, char **argv)
{
	if (ph_atoi(argv[1]) < 2 || (uint8_t)ph_atoi(argv[1]) > UINT8_MAX)
		return (1);
	if (ph_atoi(argv[2]) < 120 || (uint32_t)ph_atoi(argv[2]) > UINT32_MAX)
		return (1);
	if (ph_atoi(argv[3]) < 60 || (uint32_t)ph_atoi(argv[3]) > UINT32_MAX)
		return (1);
	if (ph_atoi(argv[4]) < 60 || (uint32_t)ph_atoi(argv[4]) > UINT32_MAX)
		return (1);
	if (argc == 6)
	{
		if (ph_atoi(argv[5]) < 1 || (uint32_t)ph_atoi(argv[5]) > UINT32_MAX)
			return (1);
	}
	return (0);
}
