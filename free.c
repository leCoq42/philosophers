#include "philo.h"

static void	stop_philo(t_philo *philos);

void	free_all(t_main *main)
{
	stop_philo(main->philos);
	/* free(main->philos); */
	/* free(main->forks); */
	/* free(main); */
}

static void	stop_philo(t_philo *philos)
{
	size_t	idx;

	idx = 0;
	while (idx < philos->main->config.num_philos)
	{
		pthread_join(philos[idx].thread, NULL);
		pthread_mutex_destroy(&philos->main->forks[idx]);
		idx++;
	}
	pthread_mutex_destroy(&philos->main->print_lock);
	pthread_mutex_destroy(&philos->main->obs_lock);
}

