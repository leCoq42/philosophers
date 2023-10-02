#include "philo.h"
#include <stdint.h>

int	observer(t_main *main)
{
	uint_fast8_t		idx;
	const uint_fast8_t	num_philos = main->config.num_philos;
	const uint_fast32_t	time_to_die_ms = main->config.time_to_die_ms;
	int					stop;
	int					state;
	uint_fast32_t		last_meal_ms;

	idx = 0;
	ph_sleep_ms(time_to_die_ms / 2);
	while (1)
	{
		pthread_mutex_lock(&main->obs_lock);
		last_meal_ms = main->philos[idx].last_meal_ms;
		state = main->philos[idx].state;
		stop = main->stop;
		pthread_mutex_unlock(&main->obs_lock);
		if (time_elapsed_ms(last_meal_ms) > time_to_die_ms && state != DONE)
		{
			pthread_mutex_lock(&main->obs_lock);
			main->stop = 1;
			main->philos[idx].state = DEAD;
			pthread_mutex_lock(&main->print_lock);
			printf(FORMAT, time_elapsed_ms(main->start_time), (uint_fast8_t)idx + 1, DIED);
			pthread_mutex_unlock(&main->print_lock);
			pthread_mutex_unlock(&main->obs_lock);
			return (1);
		}
		if (stop)
			return (1);
		idx++;
		if (idx == num_philos)
			idx = 0;
	}
	return (0);
}
