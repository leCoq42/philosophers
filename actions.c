#include "philo.h"

void	grab_forks(t_philo *philo, uint_fast8_t *forks, const uint_fast8_t uneven)
{
	/* if (uneven) */
	/* { */
	/* 	grim_reaper(philo, GRAB); */
	/* 	pthread_mutex_lock(&philo->main->forks[forks[LEFT]]); */
	/* 	grim_reaper(philo, GRAB); */
	/* 	pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]); */
	/* } */
	/* else */
	/* { */
	(void)uneven;
	grim_reaper(philo, GRAB);
	pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	grim_reaper(philo, GRAB);
	pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	/* } */
}

void	eating(t_philo *philo, uint_fast8_t *forks, const uint_fast8_t uneven)
{
	(void)uneven;
	grim_reaper(philo, EAT);
	timestamp_ms(&philo->timestamp);
	ph_sleep_ms(philo->main->config.time_to_eat_ms);
	/* if (uneven) */
	/* { */
	/* 	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]); */
	/* 	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]); */
	/* } */
	/* else */
	/* { */
	pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	/* } */
}

void	sleeping(t_philo *philo)
{
	grim_reaper(philo, SLEEP);
	ph_sleep_ms(philo->main->config.time_to_sleep_ms);
	grim_reaper(philo, THINK);
}

