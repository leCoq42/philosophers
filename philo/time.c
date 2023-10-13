/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:03:06 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/13 12:06:58 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint_fast64_t	timestamp_ms(void)
{
	struct timeval	time;
	uint_fast64_t	timestamp;

	gettimeofday(&time, NULL);
	timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (timestamp);
}

uint_fast64_t	time_diff_ms(uint64_t start_ms, uint64_t cur_ms)
{
	const uint_fast64_t	diff = cur_ms - start_ms;

	return (diff);
}

int	ph_sleep_ms(uint32_t sleeptime_ms, t_main *main)
{
	const uint_fast64_t	start_time_ms = timestamp_ms();
	const uint_fast32_t	ttd = main->config.tt_die_ms;
	uint_fast64_t		elapsed;

	if (sleeptime_ms < ttd)
		usleep(sleeptime_ms * 800);
	while (1)
	{
		elapsed = time_diff_ms(start_time_ms, timestamp_ms());
		if (elapsed >= sleeptime_ms)
			return (0);
		if (elapsed >= ttd)
			return (1);
		usleep(250);
	}
}
