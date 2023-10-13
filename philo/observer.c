/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:42:47 by mhaan             #+#    #+#             */
/*   Updated: 13/10/2023 09:48:58 AM mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo, uint32_t ttd_ms);

int	observer(t_main *main)
{
	uint_fast8_t	idx;
	const uint8_t	num_philos = main->config.num_philos;
	const uint32_t	time_to_die_ms = main->config.tt_die_ms;

	idx = 0;
	while (1)
	{
		if (check_done(main) == 1)
			return (0);
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
	if (time - philo->last_meal_ms > ttd_ms)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		set_finish(philo->main);
		usleep(3000);
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
		main->philos[idx].state = STOP;
		pthread_mutex_unlock(&main->philos[idx].philo_lock);
		idx++;
	}
}

int	check_done(t_main *main)
{
	pthread_mutex_lock(&main->stop_lock);
	if (main->philos_done >= main->config.num_philos)
	{
		pthread_mutex_unlock(&main->stop_lock);
		set_finish(main);
		usleep(3000);
		pthread_mutex_lock(&main->print_lock);
		printf("done\n");
		pthread_mutex_unlock(&main->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&main->stop_lock);
	return (0);
}
