/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:43:00 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/12 10:43:05 by mhaan            ###   ########.fr       */
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

void	ph_sleep_ms(uint32_t sleeptime_ms)
{
	const uint_fast64_t	start_time_ms = timestamp_ms();

	usleep(sleeptime_ms * 800);
	while (timestamp_ms() - start_time_ms < sleeptime_ms)
		usleep(100);
}
