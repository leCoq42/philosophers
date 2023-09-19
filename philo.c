#include "philo.h"

static void	*philo_func(void *arg);
static void	routine_loop(t_philo *philo, uint_fast8_t *forks, uint_fast32_t goal);

void	philo_run(t_main *main)
{
	uint_fast8_t	i;

	i = 0;
	pthread_mutex_lock(&main->start_lock);
	while (i < main->config.num_philos)
	{
		if (pthread_create(&main->philos[i].thread, NULL, philo_func, &main->philos[i]) != 0)
			error_exit("pthread_create error\n", 1);
		i++;
	}
	timestamp_ms(&main->start_time);
	/* printf("start time:%ld\n", main->start_time); */
	pthread_mutex_unlock(&main->start_lock);
}

static void	*philo_func(void *arg)
{
	t_philo			*philo;
	uint_fast8_t	forks[2];

	philo = (t_philo *)arg;
	forks[RIGHT] = philo->id - 1;
	forks[LEFT] = philo->id % philo->main->config.num_philos;
	pthread_mutex_lock(&philo->main->start_lock);
	pthread_mutex_unlock(&philo->main->start_lock);
	timestamp_ms(&philo->timestamp);
	/* pthread_mutex_lock(&philo->main->print_lock); */
	/* printf("philo id: %zu, right fork: %zu, left fork: %zu\n", philo->idx, forks[RIGHT], forks[LEFT]); */
	/* pthread_mutex_unlock(&philo->main->print_lock); */
	routine_loop(philo, forks, philo->main->config.num_times_to_eat);
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->main->philos_done++;
	pthread_mutex_unlock(&philo->main->obs_lock);
	return (NULL);
}

static void	routine_loop(t_philo *philo, uint_fast8_t *forks, uint_fast32_t goal)
{
	const uint_fast8_t	uneven = philo->id % 2;
	uint_fast32_t		i;

	i = 0;
	if (uneven)
		ph_sleep_ms(philo->main->config.time_to_eat_ms / 2);
	while (1)
	{
		if (goal != 0 && i >= goal)
			break ;
		grab_forks(philo, forks, uneven);
		eating(philo);
		down_forks(philo, forks, uneven);
		sleeping(philo);
		thinking(philo);
		if (i == INT_FAST32_MAX)
			i = 0;
		else
			i++;
	}
}

int	grim_reaper(t_philo *philo)
{
	uint_fast32_t	last_meal_ms;

	last_meal_ms = time_elapsed_ms(philo->timestamp);
	if (last_meal_ms > philo->main->config.time_to_die_ms)
	{
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, DIED);
		pthread_mutex_lock(&philo->main->obs_lock);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->main->obs_lock);
		return (1);
	}
	return (0);
}
