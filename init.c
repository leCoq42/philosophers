#include "philo.h"

static int	init_config(t_main *main, int argc, char **argv);
static int	init_philos(t_main *main);
static int	init_forks(t_main *main);
static int	check_config_params(t_config config, int argc);

t_main	*init_main(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	memset(main, 0, sizeof(t_main));
	main->philos_done = 0;
	pthread_mutex_init(&main->print_lock, NULL);
	pthread_mutex_init(&main->obs_lock, NULL);
	pthread_mutex_init(&main->start_lock, NULL);
	if (init_config(main, argc, argv) != 0)
		return (free_all(main), NULL);
	if (init_forks(main) != 0)
		return (free_all(main), NULL);
	if (init_philos(main) != 0)
		return (free_all(main), NULL);
	return (main);
}

static int	init_config(t_main *main, int argc, char **argv)
{
	t_config	config;

	config.num_philos = (uint8_t)ph_atoi(argv[1]);
	config.time_to_die = (size_t)ph_atoi(argv[2]) * 1000;
	config.time_to_eat = (size_t)ph_atoi(argv[3]) * 1000;
	config.time_to_sleep = (size_t)ph_atoi(argv[4]) * 1000;
	if (argc == 6)
		config.num_times_to_eat = ph_atoi(argv[5]);
	else
		config.num_times_to_eat = -1;
	if (check_config_params(config, argc) != 0)
		return ( -1);
	main->config = config;
	return (0);
}

static int	check_config_params(t_config config, int argc)
{
	if (config.num_philos < 1)
		return (-1);
	if (config.time_to_die < 1)
		return (-1);
	if (config.time_to_eat < 1)
		return (-1);
	if (config.time_to_sleep < 1)
		return (-1);
	if (argc == 6 && config.num_times_to_eat < 1)
		return (-1);
	return (0);
}

static int	init_philos(t_main *main)
{
	size_t	idx;
	
	idx = 0;
	main->philos = malloc(sizeof(t_philo) * (main->config.num_philos));
	if (!(main->philos))
		return (-1);
	memset(main->philos, 0, sizeof(t_philo) * (main->config.num_philos));
	while(idx < main->config.num_philos)
	{
		/* main->philos[idx] = malloc(sizeof(t_philo)); */
		/* if (!(main->philos[idx])) */
		/* 	return (-1); */
		/* memset(main->philos[idx], 0, sizeof(t_philo)); */
		main->philos[idx].main = main;
		main->philos[idx].idx = idx + 1;
		main->philos[idx].state = SLEEPING;
		main->philos[idx].time_of_last_meal = 0;
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
		return (-1);
	memset(main->forks, 0 , sizeof(pthread_mutex_t) * (main->config.num_philos));
	while (idx < main->config.num_philos)
	{
		/* main->forks[idx] = malloc(sizeof(pthread_mutex_t)); */
		/* if (!(main->forks[idx])) */
		/* 	return (-1); */
		/* memset(main->forks[idx], 0, sizeof(pthread_mutex_t)); */
		if (pthread_mutex_init(&main->forks[idx], NULL) != 0)
			return (-1);
		idx++;
	}
	return (0);
}
