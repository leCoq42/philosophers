#include "philo.h"
#include <stdint.h>

uint_fast64_t	timestamp_ms(void)
{
	struct timeval	time;
	uint_fast64_t	timestamp;

	gettimeofday(&time, NULL);
	timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (timestamp);
}

uint_fast32_t	time_elapsed_ms(uint_fast64_t start_time_ms)
{
	struct timeval	cur;
	uint_fast32_t	passed;

	gettimeofday(&cur, NULL);
	passed = (cur.tv_sec * 1000 + cur.tv_usec / 1000) - start_time_ms;
	return (passed);
}

void	ph_sleep_ms(uint_fast32_t sleeptime_ms)
{
	uint_fast64_t	start_time_ms;

	start_time_ms = timestamp_ms();
	while (timestamp_ms() - start_time_ms < sleeptime_ms)
		usleep(250);
}
