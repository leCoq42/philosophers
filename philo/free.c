#include "philo.h"

void	end_program(t_main *main)
{
	if (main->config.num_philos != 1)
	{
		join_threads(main, main->config.num_philos);
		destroy_mutexes(main, main->config.num_philos);
	}
	free_all(main);
}

void	free_all(t_main *main)
{
	if (main && main->philos)
		free(main->philos);
	if (main && main->forks)
		free(main->forks);
	if (main)
		free(main);
}

void	join_threads(t_main *main, uint8_t num)
{
	uint8_t	idx;

	idx = 0;
	while (idx < num)
	{
		pthread_join(main->philos[idx].thread, NULL);
		idx++;
	}
}

void	destroy_mutexes(t_main *main, uint8_t num)
{
	uint8_t	idx;

	idx = 0;
	while (idx < num)
	{
		pthread_mutex_destroy(&main->forks[idx]);
		pthread_mutex_destroy(&main->philos[idx].philo_lock);
		idx++;
	}
	pthread_mutex_destroy(&main->start_lock);
	pthread_mutex_destroy(&main->print_lock);
	pthread_mutex_destroy(&main->stop_lock);
}
