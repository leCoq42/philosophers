#include "philo.h"

uint_fast64_t	timestamp_ms(void)
{
	struct timeval	time;
	uint_fast64_t	timestamp;

	gettimeofday(&time, NULL);
	timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (timestamp);
}

uint_fast64_t	time_diff_ms(uint_fast64_t start_ms, uint_fast64_t cur_ms)
{
	const uint_fast64_t	diff = cur_ms - start_ms;

	return (diff);
}

void	ph_sleep_ms(uint_fast32_t sleeptime_ms)
{
	const uint_fast64_t	start_time_ms = timestamp_ms();
	const uint_fast64_t	sleep_us = sleeptime_ms * 800;

	usleep(sleep_us);
	while (timestamp_ms() < start_time_ms + sleeptime_ms)
		usleep(100);
}
