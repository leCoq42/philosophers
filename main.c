#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
	{
		ph_putstr_fd("Error: Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_times_to_eat]\n", 1);
		return (1);
	}
	main = init_main(argc, argv);
	if (!main)
	{
		ph_putstr_fd("init error!\n", 2);
		return (1);
	}
	philo_run(main);
	observer(main);
	free_all(main);
	return (0);
}
