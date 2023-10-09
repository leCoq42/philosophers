#include "philo.h"

static int	check_death(t_main *main, uint8_t idx, uint32_t ttd_ms);

int	observer(t_main *main)
{
	uint8_t			idx;
	const uint8_t	num_philos = main->config.num_philos;
	const uint32_t	time_to_die_ms = main->config.time_to_die_ms;
	bool			stop;

	idx = 0;
	while (1)
	{
		pthread_mutex_lock(&main->stop_lock);
		stop = main->stop;
		pthread_mutex_unlock(&main->stop_lock);
		if (stop)
			return (1);
		if (check_death(main, idx, time_to_die_ms))
			return (1);
		idx++;
		if (idx == num_philos)
		{
			idx = 0;
			usleep(50);
		}
	}
}

static int	check_death(t_main *main, uint8_t idx, uint32_t ttd_ms)
{
	uint64_t	elapsed;
	uint64_t	last_meal_ms;
	int			state;

	pthread_mutex_lock(&main->philos[idx].philo_lock);
	last_meal_ms = main->philos[idx].last_meal_ms;
	state = main->philos[idx].state;
	pthread_mutex_unlock(&main->philos[idx].philo_lock);
	if (time_diff_ms(last_meal_ms, timestamp_ms()) > ttd_ms && state != DONE)
	{
		pthread_mutex_lock(&main->stop_lock);
		main->stop = true;
		pthread_mutex_unlock(&main->stop_lock);
		elapsed = time_diff_ms(main->start_time, timestamp_ms());
		pthread_mutex_lock(&main->print_lock);
		printf(FORMAT, elapsed, idx + 1, DIED);
		pthread_mutex_unlock(&main->print_lock);
		return (1);
	}
	return (0);
}
