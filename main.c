#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		error_exit(USAGE, 2);
	main = init_main(argc, argv);
	if (!main)
		error_exit("init error!\n", 2);
	philo_run(main);
	observer(main);
	free_all(main);
	return(0);
}

