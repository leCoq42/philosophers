#include "philo.h"

static void	join_threads(t_main *main);
static void	destroy_mutexes(t_main *main);

void	free_all(t_main *main)
{
	join_threads(main);
	destroy_mutexes(main);
	free(main->philos);
	free(main->forks);
	free(main);
}

static void	join_threads(t_main *main)
{
	size_t	idx;

	idx = 0;
	while (idx < main->config.num_philos)
	{
		pthread_join(main->philos[idx].thread, NULL);
		idx++;
	}
}

static void	destroy_mutexes(t_main *main)
{
	size_t	idx;

	idx = 0;
	while (idx < main->config.num_philos)
	{
		pthread_mutex_destroy(&main->forks[idx]);
		idx++;
	}
	pthread_mutex_destroy(&main->start_lock);
	pthread_mutex_destroy(&main->print_lock);
	pthread_mutex_destroy(&main->obs_lock);
}
