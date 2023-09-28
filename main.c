#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
	{
		ph_putstr_fd("Error: Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_times_to_eat]\n", 1);
		return (1);
	}
	if (input_check(argc, argv))
		return (1);
	main = init_main(argc, argv);
	if (!main)
	{
		ph_putstr_fd("init error!\n", 2);
		return (free_all(main), 1);
	}
	if (create_threads(main) == 1)
		return (free_all(main), 1);
	observer(main);
	join_threads(main, main->config.num_philos);
	destroy_mutexes(main, main->config.num_philos);
	free_all(main);
	return (0);
}
