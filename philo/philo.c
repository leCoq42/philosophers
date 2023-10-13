/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:42:53 by mhaan             #+#    #+#             */
/*   Updated: 12/10/2023 03:23:40 PM mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_func(void *arg);
static void	set_full(t_philo *philo);

int	create_threads(t_main *main)
{
	uint_fast8_t	i;

	i = 0;
	pthread_mutex_lock(&main->start_lock);
	while (i < main->config.num_philos)
	{
		if (pthread_create(&main->philos[i].thread, NULL, philo_func, \
					&main->philos[i]) != 0)
		{
			pthread_mutex_unlock(&main->start_lock);
			return (join_threads(main, i), 1);
		}
		i++;
	}
	main->start_time = timestamp_ms();
	i = 0;
	while (i < main->config.num_philos)
		main->philos[i++].last_meal_ms = main->start_time;
	pthread_mutex_unlock(&main->start_lock);
	return (0);
}

static void	*philo_func(void *arg)
{
	t_philo	*philo;
	uint8_t	forks[2];
	uint8_t	uneven;

	philo = (t_philo *)arg;
	uneven = philo->id % 2;
	forks[RIGHT] = philo->id - 1;
	forks[LEFT] = philo->id % philo->main->config.num_philos;
	pthread_mutex_lock(&philo->main->start_lock);
	pthread_mutex_unlock(&philo->main->start_lock);
	routine_loop(philo, forks, philo->main->config.num_times_to_eat, \
				uneven);
	return (NULL);
}

int	routine_loop(t_philo *philo, uint8_t *forks, uint32_t goal, \
				uint8_t uneven)
{
	uint_fast32_t	i;

	i = 0;
	if (uneven)
	{
		check_print(philo, THINK);
		if (ph_sleep_ms(philo->main->config.tt_eat_ms / 2, philo->main) == 1)
			return (1);
	}
	while (1)
	{
		if (grab_forks(philo, forks) == 1)
			return (1);
		if (eating(philo, forks) == 1)
			return (1);
		if (++i >= goal && goal != 0)
			set_full(philo);
		if (sleeping(philo) == 1)
			return (1);
		if (i == UINT_FAST32_MAX)
			i = 0;
	}
}

static void	set_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->state == ALIVE)
	{
		philo->state = FULL;
		pthread_mutex_unlock(&philo->philo_lock);
		pthread_mutex_lock(&philo->main->stop_lock);
		philo->main->philos_done++;
		pthread_mutex_unlock(&philo->main->stop_lock);
	}
	else
		pthread_mutex_unlock(&philo->philo_lock);
}

int	check_print(t_philo *philo, char *action)
{
	uint8_t			state;
	uint_fast64_t	elapsed;

	pthread_mutex_lock(&philo->main->print_lock);
	pthread_mutex_lock(&philo->philo_lock);
	state = philo->state;
	pthread_mutex_unlock(&philo->philo_lock);
	if (state == STOP)
	{
		pthread_mutex_unlock(&philo->main->print_lock);
		return (1);
	}
	elapsed = time_diff_ms(philo->main->start_time, timestamp_ms());
	printf(FORMAT, elapsed, philo->id, action);
	pthread_mutex_unlock(&philo->main->print_lock);
	return (0);
}
