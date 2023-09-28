#include "philo.h"

void	timestamp_ms(uint_fast64_t *start_time_ms)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	*start_time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
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
	uint_fast32_t	elapsed_ms;

	timestamp_ms(&start_time_ms);
	while (1)
	{
		elapsed_ms = time_elapsed_ms(start_time_ms);
		if (elapsed_ms >= sleeptime_ms)
			return ;
		usleep(250);
	}
}
