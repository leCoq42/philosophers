#include "philo.h"

static int	check_death(t_philo *philo, uint32_t ttd_ms);

int	observer(t_main *main)
{
	uint_fast8_t	idx;
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
		if (check_death(&main->philos[idx], time_to_die_ms))
			return (1);
		idx++;
		if (idx == num_philos)
		{
			idx = 0;
			usleep(100);
		}
	}
}

static int	check_death(t_philo *philo, uint32_t ttd_ms)
{
	uint_fast64_t		elapsed;
	const uint_fast64_t	time = timestamp_ms();

	pthread_mutex_lock(&philo->philo_lock);
	if (time - philo->last_meal_ms > ttd_ms && philo->state != DONE)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		set_finish(philo->main);
		usleep(1000);
		pthread_mutex_lock(&philo->main->print_lock);
		elapsed = time_diff_ms(philo->main->start_time, timestamp_ms());
		printf(FORMAT, elapsed, philo->id, DIED);
		pthread_mutex_unlock(&philo->main->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (0);
}

void	set_finish(t_main *main)
{
	uint_fast8_t	idx;

	idx = 0;
	while (idx < main->config.num_philos)
	{
		pthread_mutex_lock(&main->philos[idx].philo_lock);
		main->philos[idx].state = DONE;
		pthread_mutex_unlock(&main->philos[idx].philo_lock);
		idx++;
	}
}
