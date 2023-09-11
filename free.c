#include "philo.h"

/* static void	free_philos(t_philo *philos); */
/* static void	free_config(t_config config); */
/* static void	free_forks(pthread_mutex_t *forks); */
/**/
/* static void	free_philos(t_philo *philos) */
/* { */
	/* int	idx; */
	/**/
	/* idx = 0; */
	/* while (philos[idx]) */
	/* { */
	/* 	free(philos[idx]); */
	/* 	idx++; */
	/* } */
	/* free(philos[idx]); */
	/* free(philos); */
/* } */
/**/
/* static void	free_config(t_config *config) */
/* { */
/* 	free(config); */
/* } */
/**/
/* static void	free_forks(pthread_mutex_t **forks) */
/* { */
/* 	int	idx; */
/**/
/* 	idx = 0; */
/* 	while (forks[idx]) */
/* 	{ */
/* 		pthread_mutex_destroy(forks[idx]); */
/* 		idx++; */
/* 	} */
/* 	free(forks); */
/* } */
/**/
/* void	free_all(t_main *main) */
/* { */
/* 	if (main->philos) */
/* 		free_philos(main->philos); */
/* 	if (main->forks) */
/* 		free_forks(main->forks); */
/* 	if (main->config) */
/* 		free_config(main->config); */
/* 	free(main); */
/* } */

void	join_threads(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx > philos->main->config.num_philos)
	{
		pthread_join(philos[idx].tid, NULL);
		idx++;
	}
}

void	free_all(t_main *main)
{
	free(main->philos);
	free(main->forks);
	free(main);
}
