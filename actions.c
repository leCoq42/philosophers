#include "philo.h"

int_fast8_t	grab_forks(t_philo *philo, uint_fast8_t *forks)
{
	pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	if (grim_reaper(philo, GRAB) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		return (1);
	}
	pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	if (grim_reaper(philo, GRAB) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	return (0);
}

int_fast8_t	eating(t_philo *philo, uint_fast8_t *forks)
{
	if (grim_reaper(philo, EAT) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	timestamp_ms(&philo->timestamp);
	ph_sleep_ms(philo->main->config.time_to_eat_ms);
	return (0);
}

int_fast8_t	sleeping(t_philo *philo, uint_fast8_t *forks)
{
	if (grim_reaper(philo, SLEEP) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	ph_sleep_ms(philo->main->config.time_to_sleep_ms);
	if (grim_reaper(philo, THINK) == 1)
		return (1);
	return (0);
}

