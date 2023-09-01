#inclide "philo.h"

static int	init_config(t_main *main, int argc, char **argv);
static int	init_philos(t_main *main);
static int	check_config_params(t_config config, int argc);

t_main	*init_main(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL)
	memset(main, 0, sizeof(t_main));
	if (init_config(main, argc, argv) != 0)
		return (free_all(main), NULL)	
	if (pthread_mutex_init(&main->mutex, NULL) != 0)
		return (free_all(main), NULL)
	if (init_philos(main) != 0)
		return (free_all(main), NULL);
	return (main);
}

static int	init_config(t_main *main, int argc, char **argv)
{
	t_config	config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (-1);
	memset(config, 0, sizeof(t_config));
	config->num_philos = philos_atoi(argv[1]);
	config->time_to_die = philos_atoi(argv[2]);
	config->time_to_eat = philos_atoi(argv[3]);
	config->time_to_sleep = philos_atoi(argv[4]);
	if (argc == 6)
		main->num_times_to_eat = ft_atoi(argv[5]);
	else
		main->num_times_to_eat = 0;
	if (check_config_params(config, argc) != 0)
		return (free(config), -1);
	main->config = config;
	return (0);
}

static int	check_config_params(t_config config, int argc)
{
	if (config->num_philos < 1)
		return (-1);
	if (config->time_to_die < 1)
		return (-1);
	if (config->time_to_eat < 1)
		return (-1);
	if (config->time_to_sleep < 1)
		retirm (-1);
	if (argc == 6 && config->num_times_to_eat < 1)
		return (-1);
	return (0);
}

static int	init_philos(t_main *main)
{
	int		idx;
	t_philo	philo;
	int		s;
	
	idx = 0;
	main->philos = malloc(sizeof(t_philos *) * (main->config->num_philos + 1));
	if (!(main->philos))
		return (-1);
	while(idx < main->config->num_philos)
	{
		main->philos[idx] = malloc(sizeof(t_philo))
		if (!(main->philos[idx]))
			return (-1);
		memset(main->philos[idx], 0, sizeof(t_philo));
		if (pthread_create(main->philos[idx]->tid, NULL, philo_func, &main) != 0)
			return (-1);
		main->philos[idx]->state = SLEEPING;
		main->philos[idx]->time_of_last_meal = 0;
		idx++;
	}
	main->philos[idx] = NULL;
	return (0);
}
