#include "philo.h"

int	observer(t_main *main)
{
	uint_fast8_t		idx;
	const uint_fast8_t	num_philos = main->config.num_philos;
	const uint_fast32_t	time_to_die_ms = main->config.time_to_die_ms;
	uint_fast32_t		last_meal_ms;

	idx = 0;
	ph_sleep_ms(main->config.time_to_die_ms - 1);
	while (1)
	{
		pthread_mutex_lock(&main->obs_lock);
		last_meal_ms = time_elapsed_ms(main->philos[idx].timestamp);
		if (main->philos_done >= num_philos)
		{
			main->stop = 1;
			pthread_mutex_lock(&main->print_lock);
			printf("All philosophers done eating.\n");
			pthread_mutex_unlock(&main->print_lock);
			pthread_mutex_unlock(&main->obs_lock);
			return (1);
		}
		pthread_mutex_unlock(&main->obs_lock);
		pthread_mutex_lock(&main->obs_lock);
		if (last_meal_ms > time_to_die_ms && main->philos[idx].state != DONE)
		{
			main->stop = 1;
			main->philos[idx].state = DEAD;
			pthread_mutex_lock(&main->print_lock);
			printf(FORMAT, time_elapsed_ms(main->start_time), (size_t)idx + 1, DIED);
			pthread_mutex_unlock(&main->print_lock);
			pthread_mutex_unlock(&main->obs_lock);
			return (1);
		}
		pthread_mutex_unlock(&main->obs_lock);
		idx++;
		if (idx == main->config.num_philos)
			idx = 0;
	}
	return (0);
}
