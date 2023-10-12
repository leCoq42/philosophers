/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:42:32 by mhaan             #+#    #+#             */
/*   Updated: 2023/10/12 10:42:37 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_config(t_main *main, int argc, char **argv);
static int	init_philos(t_main *main);
static int	init_forks(t_main *main);

t_main	*init_structs(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	memset(main, 0, sizeof(t_main));
	main->philos_done = 0;
	pthread_mutex_init(&main->print_lock, NULL);
	pthread_mutex_init(&main->stop_lock, NULL);
	pthread_mutex_init(&main->start_lock, NULL);
	if (init_config(main, argc, argv) != 0)
		return (free(main), NULL);
	if (init_forks(main) != 0)
		return (free(main), NULL);
	if (init_philos(main) != 0)
		return (free(main), free(main->forks), NULL);
	return (main);
}

static int	init_config(t_main *main, int argc, char **argv)
{
	t_config	config;

	config.num_philos = (uint8_t)ph_atoi(argv[1]);
	config.time_to_die_ms = (uint32_t)ph_atoi(argv[2]);
	config.time_to_eat_ms = (uint32_t)ph_atoi(argv[3]);
	config.time_to_sleep_ms = (uint32_t)ph_atoi(argv[4]);
	if (argc == 6)
		config.num_times_to_eat = (uint32_t)ph_atoi(argv[5]);
	else
		config.num_times_to_eat = 0;
	main->config = config;
	return (0);
}

static int	init_philos(t_main *main)
{
	size_t	idx;

	idx = 0;
	main->philos = malloc(sizeof(t_philo) * (main->config.num_philos));
	if (!(main->philos))
		return (1);
	memset(main->philos, 0, sizeof(t_philo) * (main->config.num_philos));
	while (idx < main->config.num_philos)
	{
		pthread_mutex_init(&main->philos[idx].philo_lock, NULL);
		main->philos[idx].main = main;
		main->philos[idx].id = idx + 1;
		main->philos[idx].state = ALIVE;
		idx++;
	}
	return (0);
}

static int	init_forks(t_main *main)
{
	size_t	idx;

	idx = 0;
	main->forks = malloc(sizeof(pthread_mutex_t) * (main->config.num_philos));
	if (!(main->forks))
		return (1);
	memset(main->forks, 0, sizeof(pthread_mutex_t) * (main->config.num_philos));
	while (idx < main->config.num_philos)
	{
		if (pthread_mutex_init(&main->forks[idx], NULL) != 0)
			return (destroy_mutexes(main, idx), free(main->forks), 1);
		idx++;
	}
	return (0);
}
