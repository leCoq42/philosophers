/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:42:15 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/12 10:42:21 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(int argc, char **argv)
{
	if (ph_atoi(argv[1]) < 1 || ph_atoi(argv[1]) > 200)
		return (1);
	if (ph_atoi(argv[2]) < 60 || ph_atoi(argv[2]) > UINT32_MAX)
		return (1);
	if (ph_atoi(argv[3]) < 60 || ph_atoi(argv[3]) > UINT32_MAX)
		return (1);
	if (ph_atoi(argv[4]) < 60 || ph_atoi(argv[4]) > UINT32_MAX)
		return (1);
	if (argc == 6)
	{
		if (ph_atoi(argv[5]) < 1 || ph_atoi(argv[5]) > UINT32_MAX)
			return (1);
	}
	return (0);
}

void	print_usage_error(void)
{
	ph_putstr_fd("Error: Usage: ./philo num_philos time_to_die ", 1);
	ph_putstr_fd("time_to_eat time_to_sleep [num_times_to_eat]\n", 1);
}
