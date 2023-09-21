#include "philo.h"

void	grab_forks(t_philo *philo, uint_fast8_t *forks, const uint_fast8_t uneven)
{
	if (uneven)
	{
		if (grim_reaper(philo) == 0)
		{
			pthread_mutex_lock(&philo->main->print_lock);
			printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, GRAB);
			pthread_mutex_unlock(&philo->main->print_lock);
		}
		pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
		if (grim_reaper(philo) == 0)
		{
			pthread_mutex_lock(&philo->main->print_lock);
			printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, GRAB);
			pthread_mutex_unlock(&philo->main->print_lock);
		}
		pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
	}
	else
	{
		if (grim_reaper(philo) == 0)
		{
			pthread_mutex_lock(&philo->main->print_lock);
			printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, GRAB);
			pthread_mutex_unlock(&philo->main->print_lock);
		}
		pthread_mutex_lock(&philo->main->forks[forks[RIGHT]]);
		if (grim_reaper(philo) == 0)
		{
			pthread_mutex_lock(&philo->main->print_lock);
			printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, GRAB);
			pthread_mutex_unlock(&philo->main->print_lock);
		}
		pthread_mutex_lock(&philo->main->forks[forks[LEFT]]);
	}
}

void	eating(t_philo *philo)
{
	if (grim_reaper(philo) == 0)
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, EAT);
		pthread_mutex_unlock(&philo->main->print_lock);
	}
	timestamp_ms(&philo->timestamp);
	ph_sleep_ms(philo->main->config.time_to_eat_ms);
}

void	down_forks(t_philo *philo, uint_fast8_t *forks, const uint_fast8_t uneven)
{
	if (uneven)
	{
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
	}
	else
	{
		pthread_mutex_unlock(&philo->main->forks[forks[RIGHT]]);
		pthread_mutex_unlock(&philo->main->forks[forks[LEFT]]);
	}
}

void	sleeping(t_philo *philo)
{
	if (grim_reaper(philo) == 0)
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, SLEEP);
		pthread_mutex_unlock(&philo->main->print_lock);
	}
	ph_sleep_ms(philo->main->config.time_to_sleep_ms);
}

void	thinking(t_philo *philo)
{
	if (grim_reaper(philo) == 0)
	{
		pthread_mutex_lock(&philo->main->print_lock);
		printf(FORMAT, time_elapsed_ms(philo->main->start_time), philo->id, THINK);
		pthread_mutex_unlock(&philo->main->print_lock);
	}
}
