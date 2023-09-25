#include "philo.h"

static void	*philo_func(void *arg);
static int	routine_loop(t_philo *philo, uint_fast8_t *forks, uint_fast32_t goal);

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
	timestamp_ms(&philo->timestamp);
	pthread_mutex_lock(&philo->main->start_lock);
	pthread_mutex_unlock(&philo->main->start_lock);
	/* pthread_mutex_lock(&philo->main->print_lock); */
	/* printf("philo id: %zu, right fork: %hhu, left fork: %hhu\n", philo->id, forks[RIGHT], forks[LEFT]); */
	/* pthread_mutex_unlock(&philo->main->print_lock); */
	if (routine_loop(philo, forks, philo->main->config.num_times_to_eat) == 1)
		return (NULL);
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->main->philos_done++;
	pthread_mutex_unlock(&philo->main->obs_lock);
	return (NULL);
}

static int	routine_loop(t_philo *philo, uint_fast8_t *forks, uint_fast32_t goal)
{
	const uint_fast8_t	uneven = philo->id % 2;
	uint_fast32_t		i;

	i = 0;
	if (uneven)
		ph_sleep_ms(philo->main->config.time_to_sleep_ms / 2);
		/* sleeping(philo, forks); */
	while (1)
	{
		if (goal != 0 && i >= goal)
			return (0);
		if (grab_forks(philo, forks) == 1)
			return (1);
		if (eating(philo, forks) == 1)
			return (1);
		if (sleeping(philo, forks) == 1)
			return (1);
		if (i == UINT_FAST32_MAX)
			i = 0;
		else
			i++;
	}
}

int_fast8_t	grim_reaper(t_philo *philo, char *action)
{
	uint_fast32_t	last_meal_ms;

	last_meal_ms = time_elapsed_ms(philo->timestamp);

	pthread_mutex_lock(&philo->main->obs_lock);
	if (philo->main->state == DEAD)
	{
		pthread_mutex_unlock(&philo->main->obs_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->obs_lock);
	if (last_meal_ms > philo->main->config.time_to_die_ms)
	{
		pthread_mutex_lock(&philo->main->obs_lock);
		philo->main->state = DEAD;
		pthread_mutex_unlock(&philo->main->obs_lock);
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, DIED);
		pthread_mutex_unlock(&philo->main->print_lock);
		return (1);
	}
	pthread_mutex_lock(&philo->main->print_lock);
	printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, action);
	pthread_mutex_unlock(&philo->main->print_lock);
	return (0);
}
