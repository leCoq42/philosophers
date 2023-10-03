#include "philo.h"
#include <stdint.h>

static void	*philo_func(void *arg);
static void	set_done(t_philo *philo);

int	create_threads(t_main *main)
{
	uint_fast8_t	i;

	i = 0;
	pthread_mutex_lock(&main->start_lock);
	while (i < main->config.num_philos)
	{
		if (pthread_create(&main->philos[i].thread, NULL, philo_func, &main->philos[i]) != 0)
			return (join_threads(main, i), 1);
		i++;
	}
	main->start_time = timestamp_ms();
	pthread_mutex_unlock(&main->start_lock);
	return (0);
}

static void	*philo_func(void *arg)
{
	t_philo	*philo;
	uint8_t	forks[2];
	uint8_t	uneven;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->last_meal_ms = timestamp_ms();
	pthread_mutex_unlock(&philo->main->obs_lock);
	uneven = philo->id % 2;
	forks[RIGHT] = philo->id - 1;
	forks[LEFT] = philo->id % philo->main->config.num_philos;
	pthread_mutex_lock(&philo->main->start_lock);
	pthread_mutex_unlock(&philo->main->start_lock);
	if (routine_loop(philo, forks, philo->main->config.num_times_to_eat, uneven) == 0)
		set_done(philo);
	return (NULL);
}

int	routine_loop(t_philo *philo, uint8_t *forks, uint32_t goal, uint8_t uneven)
{
	uint_fast32_t	i;

	i = 0;
	if (uneven)
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, THINK);
		pthread_mutex_unlock(&philo->main->print_lock);
		ph_sleep_ms(philo->main->config.time_to_sleep_ms / 2);
	}
	while (1)
	{
		if (grab_forks(philo, forks) == 1)
			return (1);
		if (eating(philo, forks) == 1)
			return (1);
		if (goal != 0 && ++i >= goal)
			return (0);
		if (sleeping(philo) == 1)
			return (1);
		if (i == UINT_FAST32_MAX)
			i = 0;
	}
}

static void	set_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->state = DONE;
	philo->main->philos_done++;
	if (philo->main->philos_done >= philo->main->config.num_philos)
	{
		philo->main->stop = 1;
		pthread_mutex_unlock(&philo->main->obs_lock);
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, SLEEP);
		printf("All philosophers done eating.\n");
		pthread_mutex_unlock(&philo->main->print_lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->main->obs_lock);
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, SLEEP);
		pthread_mutex_unlock(&philo->main->print_lock);
	}
}


int	check_print(t_philo *philo, char *action)
{
	int stop;

	pthread_mutex_lock(&philo->main->obs_lock);
	stop = philo->main->stop;
	pthread_mutex_unlock(&philo->main->obs_lock);
	if (stop)
		return (1);
	pthread_mutex_lock(&philo->main->print_lock);
	printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, action);
	pthread_mutex_unlock(&philo->main->print_lock);
	return (0);
}
