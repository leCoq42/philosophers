#include "philo.h"

int	grab_forks(t_philo *philo, uint8_t *forks)
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
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo, uint8_t *forks)
{
	uint64_t	timestamp;

	if (check_print(philo, EAT) == 1)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		return (1);
	}
	timestamp = timestamp_ms();
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_ms = timestamp;
	pthread_mutex_unlock(&philo->philo_lock);
	ph_sleep_ms(philo->main->config.time_to_eat_ms);
	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (check_print(philo, SLEEP) == 1)
		return (1);
	ph_sleep_ms(philo->main->config.time_to_sleep_ms);
	if (check_print(philo, THINK) == 1)
		return (1);
	return (0);
}
