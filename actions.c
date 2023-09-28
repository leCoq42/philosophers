#include "philo.h"

int	grab_forks(t_philo *philo, uint_fast8_t *forks)
{
	pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	if (check_print(philo, GRAB) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		return (1);
	}
	pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	if (check_print(philo, GRAB) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo, uint_fast8_t *forks)
{
	uint_fast64_t timestamp;

	if (check_print(philo, EAT) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	timestamp_ms(&timestamp);
	pthread_mutex_lock(&philo->main->obs_lock);
	philo->last_meal_ms = timestamp;
	pthread_mutex_unlock(&philo->main->obs_lock);
	ph_sleep_ms(philo->main->config.time_to_eat_ms);
	return (0);
}

int	sleeping(t_philo *philo, uint_fast8_t *forks)
{
	if (check_print(philo, SLEEP) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	ph_sleep_ms(philo->main->config.time_to_sleep_ms);
	if (check_print(philo, THINK) == 1)
		return (1);
	return (0);
}
